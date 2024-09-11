#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2tcpip")
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#endif

#if defined(_WIN32)
#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif
#define GETSOCKETERRNO() (WSAGetLastError()) 
#define CLOSESOCKET(s) (closesocket(s))
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#else
#define GETSOCKETERRNO() (errno)
#define CLOSESOCKET(s) (close(s))
#define ISVALIDSOCKET(s) (s>=0)
#define SOCKET int
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
    #if defined(_WIN32)
        WSADATA d;
        if(WSAStartup(MAKEWORD(2,2),&d)){
            fprintf(stderr,"Failed to initialise.\n");
            return 1;
        }
    #endif

    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET6;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(NULL,"8080",&hints,&bind_address);

    //create socket
    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"socket() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //make socket dual
    int option=0;
    if(setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,(void*) &option,sizeof(option))){
        fprintf(stderr,"setsockopt() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //bind address
    if(bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen)){
        fprintf(stderr,"bind().(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);
    //listen
    if(listen(socket_listen,10)<0){
        fprintf(stderr,"listen() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //accept incoming connections
    struct sockaddr_storage client_address;
    socklen_t client_len=sizeof(client_address);
    SOCKET socket_client=accept(socket_listen,(struct sockaddr*) &client_address,&client_len);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"accept() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //printing clients info
    printf("Printing clients info........\n");
    char buffer[1000];
    getnameinfo((struct sockaddr*) &client_address,client_len,buffer,sizeof(buffer),
                0,0,NI_NUMERICHOST);
    printf("%s\n",buffer);
    //request
    printf("Receiving request...\n");
    char request[1024];
    int bytes_received=recv(socket_client,request,1024,0);
    printf("%d of %d received\n",bytes_received,(int)strlen(request));

    //response
    printf("Sending response.....\n");
    const char *response=
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Local time: ";
    int bytes_sent=send(socket_client,response,strlen(response),0);
    printf("%d of %d sent\n",bytes_sent,(int)strlen(response));

    time_t timer;
    time(&timer);
    char *time_msg=ctime(&timer);
    bytes_sent=send(socket_client,time_msg,strlen(time_msg),0);
    printf("%d of %d sent.\n",bytes_sent,(int)strlen(time_msg));
    //close sockets
    printf("Closing client socket.....\n");
    CLOSESOCKET(socket_client);
    printf("Closing listening socket.....\n");
    CLOSESOCKET(socket_listen);

    #if defined(_WIN32)
        WSACleanup();
    #endif
    printf("Finished.\n");
    return 0; 
}

