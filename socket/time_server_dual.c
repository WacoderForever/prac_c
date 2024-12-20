#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600
#endif
#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define GETSOCKETERRNO()(WSAGetLastError())
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
#define ISVALIDSOCKET(s) ((s) >= 0)
#define GETSOCKETERRNO() (errno)
#define CLOSESOCKET(s) (close(s))

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    #if defined(_WIN32)
        WSADATA d;
        if(WSAStartup(MAKEWORD(2,2),&d)){
            fprintf(stderr,"Failed to initialise.\n");
            return 1;
        }
    #endif
    //local address to bind socket to
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET6;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;

    struct addrinfo *bind_addr;
    getaddrinfo(0,"8087",&hints,&bind_addr);

    //make socket
    printf("Creating socket....\n");
    SOCKET socket_listen=socket(bind_addr->ai_family,bind_addr->ai_socktype,bind_addr->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"socket() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //make socket dual by clearing thr IPV6_V6ONLY flag
    const int option=0;
    if((setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,(void*)&option,sizeof(option))) < 0){
        fprintf(stderr,"setsockopt() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //bind socket to the local address
    printf("Binding socket to local address....\n");
    if((bind(socket_listen,bind_addr->ai_addr,bind_addr->ai_addrlen)) < 0){
        fprintf(stderr,"bind() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_addr);
    //listen for connections
    printf("Listening for connections....\n");
    if((listen(socket_listen,10)) < 0){
        fprintf(stderr,"listen() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //accepting connections
    printf("Waiting for connection ......\n");
    struct sockaddr_storage client_addr;
    socklen_t client_len=sizeof(client_addr);
    SOCKET socket_client=accept(socket_listen,(struct sockaddr*)&client_addr,&client_len);
    if(!ISVALIDSOCKET(socket_client)){
        fprintf(stderr,"accept() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //print client info
    printf("Client connected.....\n");
    char buffer[100];
    getnameinfo((struct sockaddr*)&client_addr,client_len,buffer,sizeof(buffer),0,0,NI_NUMERICHOST);
    printf("%s\n",buffer);
    //receive request from client
    printf("Receiving request....\n");
    char request[1024];
    int bytes_received=recv(socket_client,request,1024,0);
    if(bytes_received<0){
        fprintf(stderr,"recv() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    printf("Bytes received: %d",bytes_received);
    printf("%.*s",bytes_received,request);
    //send response
    const char *response=
        "HTTP 1.1 200 OK \r\n"
        "Connection: close \r\n"
        "Content-Type: text/plain \r\n\r\n"
        "Local time is: ";
    printf("Sending response...\n");
    int bytes_sent=send(socket_client,response,strlen(response),0);
    if(bytes_sent < 0){
        fprintf(stderr,"send() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    printf("Sent %d of %d bytes.\n",bytes_sent,(int)strlen(response));

    time_t timer;
    time(&timer);
    char *message=ctime(&timer);
    bytes_sent=send(socket_client,message,strlen(message),0);
    if(bytes_sent < 0){
        fprintf(stderr,"send() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    printf("Sent %d of %d bytes.\n",bytes_sent,(int)strlen(message));
    //closing connection
    printf("Closing connection.....\n");
    CLOSESOCKET(socket_client);
    printf("Closing listening connection.....\n");
    CLOSESOCKET(socket_listen);

    #if defined(_WIN32)
        WSACleanup();
    #endif
    printf("Finished.\n");

    return 0;
}