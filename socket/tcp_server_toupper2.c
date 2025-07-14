#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600 
#endif
#ifndef (IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif

#pragma comment(lib,"ws2_32")

#include <ws2tcpip.h>
#include <winsock2.h>

#define GETSOCKETERRNO() (WSAGetLastError())
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) (closesocket(s))

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define SOCKET int
#define GETSOCKETERRNO() (errno)
#define ISVALIDSOCKET(s) (s >= 0)
#define CLOSESOCKET(s) (close(s))

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>

int main(){
    #if defined(_WIN32)
     WSADATA d;
     if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise winsock api.(%d)\n",GETSOCKETERRNO());
        return 1;
     }
    #endif
    puts("Socket API initialised successfully");
    
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET6;
    hints.ai_flags=AI_PASSIVE;
    hints.ai_socktype=SOCK_STREAM;
    struct addrinfo *bind_address;
    getaddrinfo(NULL,"8090",&hints,&bind_address);
    
    puts("Creating socket......");
    SOCKET socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"Failed to create socket. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    //making the socket dual
    int option=0;
    if((setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,
        (void*)&option,(socklen_t)sizeof(option)))<0){
            fprintf(stderr,"setsockopt() failed.%d\n",GETSOCKETERRNO());
            return 1;
    }

    puts("Binding the socket to the address......");
    if((bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen))<0){
        fprintf(stderr,"bind() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    puts("Listening .......");
    if((listen(socket_listen,10))<0){
        fprintf(stderr,"listen failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen,&master);
    SOCKET max_socket = socket_listen;
    puts("Waiting for connections....");
    while(1){
        fd_set reads;
        reads = master;
        if((select((max_socket+1),&reads,0,0,0))<0){
            fprintf(stderr,"select() failed. (%d)\n",GETSOCKETERRNO());
            return 1;
        }

        SOCKET i=0;
        for(i;i<=max_socket;i++){
            if(FD_ISSET(i,&reads)){
                if(i==socket_listen){
                    struct sockaddr_storage client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    puts("Accepting a new connection");
                    SOCKET socket_client = accept(socket_listen,(struct sockaddr*)&client_addr,&client_len);
                    if(!ISVALIDSOCKET(socket_client)){
                        fprintf(stderr,"accept() failed.(%d)\n",GETSOCKETERRNO());
                        return 1;
                    }
                    FD_SET(socket_client,&master);
                    if(socket_client > max_socket) max_socket=socket_client;

                    char address_buffer[100];
                    char service_buffer[100];
                    getnameinfo((struct sockaddr*)&client_addr,client_len,
                                address_buffer,sizeof(address_buffer),
                                service_buffer,sizeof(service_buffer),NI_NUMERICHOST);
                    printf("The address of the new client is : %s\n",address_buffer);
                    printf("The client is accessing the service: %s\n",service_buffer);
                }
                else{
                    char read[4096];
                    int bytes_received = recv(i,read,sizeof(read),0);
                    if(bytes_received<1){
                        FD_CLR(i,&master);
                        CLOSESOCKET(i);
                        break;
                    }
                    for(int k=0;k<bytes_received;k++) read[k]=toupper(read[k]);
                    send(i,read,bytes_received,0);
                }
            }
        }
    }

    #if defined(_WIN32)
        WSACleanup();
    #endif
    CLOSESOCKET(socket_listen);
    printf("Finished");
    return 0;
}


