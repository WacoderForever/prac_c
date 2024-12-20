#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600
#endif
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())

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
#define CLOSESOCKET(s) close(s)
#define GETSOCKETERRNO() (errno)

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
    //configuring local address that the socket will bind to
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0,"8081",&hints,&bind_address);

    //create socket 
    printf("Creating socket....\n");
    SOCKET socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"socket() failed. %d\n",GETSOCKETERRNO());
        return 1;
    }
    //binding socket to bind_address
    printf("Binding socket to local address.....\n");
    if((bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen)) < 0){
        fprintf(stderr,"bind() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    //listen for connections
    printf("Listening for connections .....\n");
    if((listen(socket_listen,10))<0){
        fprintf(stderr,"listen() failed. %d\n",GETSOCKETERRNO());
        return 1;
    }

    //accept connections
    printf("Waiting for connection......\n");
    struct sockaddr_storage client_addr;
    socklen_t client_len=sizeof(client_addr);
    SOCKET socket_client=accept(socket_listen,(struct sockaddr*) &client_addr,&client_len);
    if(!ISVALIDSOCKET(socket_client)){
        fprintf(stderr,"accept() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    //print client address
    printf("Client connected.\n");
    char buffer[100];
    getnameinfo((struct sockaddr*) &client_addr,client_len,buffer,sizeof(buffer),0,0,NI_NUMERICHOST);
    printf("%s\n",buffer);

    //receiving request from client
    printf("Receiving request...\n");
    char request[1024];
    int bytes_received=recv(socket_client,request,1024,0);
    printf("Bytes received: %d\n",bytes_received);
    printf("%.*s\n",bytes_received,request);

    //sending response
    printf("Sending response.......\n");
    const char *response=
        "HTTP/1.1 200 OK\r\n"
        "Connection: close \r\n"
        "Content-Type: text/plain \r\n\r\n"
        "Local time is: ";
    int bytes_sent=send(socket_client,response,strlen(response),0);
    printf("Sent %d of %d bytes\n",bytes_sent,(int)strlen(response));

    time_t timer;
    time(&timer);
    char *message=ctime(&timer);
    bytes_sent=send(socket_client,message,strlen(message),0);
    printf("Sent %d of %d bytes.\n",bytes_sent,(int) strlen(message));

    //close connection
    printf("Closing connection.....\n");
    CLOSESOCKET(socket_client);

    printf("Closing listening socket....\n");
    CLOSESOCKET(socket_listen);

    #if defined(_WIN32)
        WSACleanup();
    #endif

    printf("Finished\n");

    return 0;
}