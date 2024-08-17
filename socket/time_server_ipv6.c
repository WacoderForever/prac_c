#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#if defined(_WIN32)
#define GETSOCKETERRNO (WSAGetLastError())
#define CLOSESOCKET(s) closesocket(s)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#else
#define GETSOCKETERRNO (errno)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define ISVALIDSOCKET(s) (s>=0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    #if defined(_WIN32)
        WSADATA d;
        if(WSAStartup(MAKEWORD(2,2)),&d){
            fprintf(stderr,"Failed to initialise.");
            return 1;
        }
    #endif
    //getting local address the server will bind to
    struct sockaddr hints;
    hints.ai_family=AF_INET6;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;

    struct sockaddr *bind_address;
    getaddrinfo(NULL,"8080",&hints,&bind_address);

    //create socket
    printf("Creating socket.....\n");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->sock_type,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"socket() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    //bind socket to address
    printf("Binding socket to address....\n");
    if(bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen)){
        fprintf(stderr,"bind() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    //listening for connections
    printf("Listening for connections.......\n");
    if(listen(socket_listen)<0){
        fprintf(stderr,"listen() failed.(%d) \n",GETSOCKETERRNO());
        return 1;
    }

    //accept incoming connections
    struct sockaddr_storage client_address;
    socklen_t clientlen=sizeof(client_address);
    SOCKET socket_client=accept(socket_listen,(struct sockaddr*) &client_address,&client_len);
    if(!ISVALIDSOCKET(socket_client)){
        fprintf(stderr,"accept() failed.(%d) \n",GETSOCKETERRNO());
        return 1;
    }

    //printing clients info
    printf("Printing clients info........\n");
    char buffer[1000];
    getnameinfo((struct sockaddr*) &client_address,buffer,sizeof(buffer),
                0,0,NI_NUMERICHOST);
    printf("%s\n",buffer);

    //request
    printf("Receiving request...\n");
    char request[1024];
    int bytes_received=recv(socket_client,1024,0);
    printf("%d of %d received\n",bytes_received,(int)strlen(request));

    //response
    printf("Sending response.....\n");
    char *response=
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Local time: ";
    int bytes_sent=send(socket_client,sizeof(response),0);
    printf("%d of %d sent\n",bytes_sent,(int)strlen(response));

    time_t timer;
    time(&timer);
    char *time_msg=ctime(&timer);
    int bytes_sent=send(socket_client,sizeof(time_msg),0);
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