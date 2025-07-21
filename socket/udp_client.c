#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600
#endif
#pragma comment(lib,"ws2_32")
#ifndef(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif

#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define GETSOCKETERRNO() (WSAGetLastError())
#define CLOSESOCKET(s) (closesocket(s))

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#define SOCKET int
#define ISVALIDSOCKET(s) (s >= 0)
#define GETSOCKETERRNO() (errno)
#define CLOSESOCKET(s) (close(s))
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise winsock API. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    #endif
    puts("Socket API initialised successfully");
    if(argc != 3){
        fprintf(stderr,"Usage: ./udp_client host service/port.\n");
        return 1;
    }
    puts("Configuring remote address......");
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=SOCK_DGRAM;
    struct addrinfo *peer_address;
    if(getaddrinfo(argv[1],argv[2],&hints,&peer_address)){
        fprintf(stderr,"Failed to configure remote address. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    puts("Remote address is:");
    char address_buffer[100];
    char service_buffer[100];
    if(getnameinfo(peer_address->ai_addr,peer_address->ai_addrlen,
                    address_buffer,(socklen_t)sizeof(address_buffer),
                    service_buffer,(socklen_t)sizeof(service_buffer),NI_NUMERICHOST)){
        fprintf(stderr,"Failed to get the address info. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    printf("Node is: %s\n",address_buffer);
    printf("Service is: %s \n",service_buffer);
    puts("Creating socket.......");
    SOCKET socket_peer;
    socket_peer= socket(peer_address->ai_family,peer_address->ai_socktype,peer_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_peer)){
        fprintf(stderr,"Failed to create socket. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    puts("Connecting to remote server.......");
    if((connect(socket_peer,peer_address->ai_addr,peer_address->ai_addrlen))<0){
        fprintf(stderr,"Failed to connect to remote address.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    freeaddrinfo(peer_address);
    puts("Enter data followed by enter:");
    while(1){
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer,&reads);
        #if !defined(_WIN32)
            FD_SET(fileno(stdin),&reads);
        #endif
        struct timeval timeout;
        timeout.tv_sec=0;
        timeout.tv_usec=100000;

        if((select((socket_peer+1),&reads,0,0,&timeout))<0){
            fprintf(stderr,"select() failed.(%d)\n",GETSOCKETERRNO());
            return 1;
        }

        if(FD_ISSET(socket_peer,&reads)){
            char read[4096];
            int bytes_received = recv(socket_peer,read,sizeof(read),0);
            if(bytes_received < 1){
                puts("Connection closed by peer");
                break;
            }
        }

        #if defined(_WIN32)
            if(_kbhit()){
        #else
            if(FD_ISSET(fileno(stdin),&reads)){
        #endif
                char read[4096];
                if(!fgets(read,sizeof(read),stdin)) break;
                puts("Sending......."); 
                int bytes_sent = send(socket_peer,read,sizeof(read),0);
                printf("Sent: %s\n",read);
            }

    }

    #if defined(_WIN32)
     WSACleanup();
    #endif

    CLOSESOCKET(socket_peer);
    return 0;
}
