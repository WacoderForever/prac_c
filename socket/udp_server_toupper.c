#if defined (_WIN32)
#ifndef (_WIN32_WINNIT)
#define _WIN32_WINNIT 0x0600
#endif
#ifndef IPV6_V6ONLY
#define IPV6_V6ONLY 27
#endif
#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define GETSOCKETERRNO() (WSAGetLastError())
#define CLOSESOCKET(s) (closesocket(s))

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define SOCKET int
#define ISVALIDSOCKET(s) ((s) >= 0)
#define GETSOCKETERRNO() (errno)
#define CLOSESOCKET(s) (close(s))

#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialize winsock api.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    #endif
    puts("Initialised socket API successfully.");

    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET6;
    hints.ai_socktype= SOCK_DGRAM;
    hints.ai_flags=AI_PASSIVE;
    struct addrinfo *bind_address;
    if(getaddrinfo(NULL,"8090",&hints,&bind_address)<0){
        fprintf(stderr,"Failed to configure local address. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    puts("Creating socket.......");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"Failed to create listening socket. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //making the socket dual
    int option=0;
    if((setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,(void*)&option,sizeof(option)))<0){
        fprintf(stderr,"setsockopt() failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    puts("Binding the socket to the local address...");
    if((bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen))<0){
        fprintf(stderr,"Binding failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    puts("Waiting for connections.....");
    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen,&master);
    int max_socket=socket_listen;
    while(1){
        fd_set reads;
        reads = master;     
        if(select((max_socket+1),&reads,0,0,0)<0){
            fprintf(stderr,"select() failed. (%d)\n",GETSOCKETERRNO());
            return 1;
        }
        SOCKET i=1;
        for(i;i<=max_socket;i++){
            if(FD_ISSET(i,&reads)){
                struct sockaddr_storage client_addr;
                socklen_t client_len= sizeof(client_addr);
                char read[100];
                int bytes_received = recvfrom(socket_listen,read,sizeof(read),0,
                                    (struct sockaddr*) &client_addr,&client_len);
                if(bytes_received < 1){
                    fprintf(stderr,"connection closed by peer. (%d)\n",GETSOCKETERRNO());
                    return 1;
                }

                for(int j=0;j<bytes_received;j++) read[j] = toupper(read[j]);
                sendto(socket_listen,read,sizeof(read),0,(struct sockaddr*)&client_addr,client_len);
            }
        }
    }

    puts("Closing listening socket......");
    CLOSESOCKET(socket_listen);
    #if defined(_WIN32)
        WSACleanup()
    #endif

    return 0;
}