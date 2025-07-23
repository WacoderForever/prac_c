#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600
#endif
#ifndef IPV6_V6ONLY
#define IPV6_V6ONLY 27
#endif
#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>

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
#include <string.h>

int main(int argc, char **argv){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise winsock. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    #endif
    if(argc != 3){
        fprintf(stderr,"Usage: ./udp_client host port");
        return 1;
    }
    puts("Socket API initialised successfully");
    puts("Configuring remote address.....");
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_socktype=SOCK_DGRAM;
    struct addrinfo *peer_address;
    if(getaddrinfo(argv[1],argv[2],&hints,&peer_address)<0){
        fprintf(stderr,"Failed to configure remote address. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    puts("Configured remote address successfully");
    puts("Remote address:");
    char remote_address[100];
    char service[100];
    if((getnameinfo(peer_address->ai_addr,peer_address->ai_addrlen,remote_address,sizeof(remote_address),
        service,sizeof(service),NI_NUMERICHOST | NI_NUMERICSERV)) < 0){
            fprintf(stderr,"Failed to get remote address. (%d)\n",GETSOCKETERRNO());
            return 1;
    }
    printf("Host: %s\n",remote_address);
    printf("Service: %s\n",service);
    puts("Creating socket......");
    SOCKET socket_peer;
    socket_peer=socket(peer_address->ai_family,peer_address->ai_socktype,peer_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_peer)){
        fprintf(stderr,"Failed to create socket. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    struct sockaddr_storage sender;
    socklen_t sender_len=sizeof(sender);
    puts("To enter data input text followed by ENTER key");
    puts("To exit type \"exit\" followed by ENTER key");
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
            fprintf(stderr,"select() failed. (%d)\n",GETSOCKETERRNO());
            return 1;
        }
        if(FD_ISSET(socket_peer,&reads)){
            char read[4096];
            int bytes_received=recvfrom(socket_peer,read,sizeof(read),0,
                                (struct sockaddr*)&sender,&sender_len);
            if(bytes_received < 1){
                fprintf(stderr,"Peer closed connection.(%d)\n",GETSOCKETERRNO());
                break;
            }
            printf("Received: %.*s\n",bytes_received,read);
        }
    #if defined(_WIN32)
        if(_kbhit()){
    #else
        if(FD_ISSET(fileno(stdin),&reads)){
    #endif
            char read[4096];
            if(!fgets(read,sizeof(read),stdin)) break;
            if(!strncmp(read,"exit",4)) break;
            int bytes_sent=sendto(socket_peer,read,sizeof(read),0,peer_address->ai_addr,peer_address->ai_addrlen);
            printf("Sent: %.*s",bytes_sent,read);
        }
    }

    puts("Closing connection......");
    CLOSESOCKET(socket_peer);
    #if defined(_WIN32)
        WSACleanup()
    #endif
    puts("Finished......");
    return 0;
}