#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#pragma comment(lib,"ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define GETSOCKETERRNO() WSAGetLastError()
#define CLOSESOCKET(s) closesocket(s)
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
#define CLOSESOCKET(s) close(s)
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>

int main(){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to load winsock api.");
        return 1;
    }
    #endif
    printf("Socket API loaded successfully.\n");

    printf("Configuring the address the web server should bind to....\n");
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_flags=AI_PASSIVE; //for binding if node is null
    hints.ai_socktype=SOCK_STREAM;
    struct addrinfo *bind_address;
    getaddrinfo(NULL,"8088",&hints,&bind_address);

    printf("Creating socket......\n");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"Failed to create listening socket. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //binding the address
    printf("Binding the socket to our address......\n");
    if(bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen)){
        fprintf(stderr,"Failed to bind the socket to the address. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);
    //listening
    printf("Socket is listening........\n");
    if((listen(socket_listen,10))< 0){
        fprintf(stderr,"Listening failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    //accepting connections
    printf("Waiting for connection......\n");
    struct sockaddr_storage client_addr;
    socklen_t client_len = sizeof(client_addr);
    //accept also fills the address info of the client that connected
    SOCKET socket_client = accept(socket_listen,(struct sockaddr*)&client_addr,&client_len);
    if(!ISVALIDSOCKET(socket_client)){
        fprintf(stderr,"Failed to accept connections.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    printf("Client is connected......\n");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo((struct sockaddr*)&client_addr,client_len,address_buffer,(socklen_t)sizeof(address_buffer),
                service_buffer,(socklen_t)sizeof(service_buffer),NI_NUMERICHOST);
    printf("Host info: %s\n",address_buffer);
    printf("Service info: %s\n",service_buffer);

    //request
    printf("Reading request.....\n");
    char request[1024];
    int bytes_received = recv(socket_client,request,1024,0);
    printf("Bytes received: %d\n",bytes_received);
    printf("Request received: %.*s\n",bytes_received,request);

    //response
    printf("Sending reponse....\n");
    const char* response = 
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Local Time: ";
    int bytes_sent = send(socket_client,response,strlen(response),0);
    printf("Sent %d of %d bytes.\n",bytes_sent,(int)strlen(response));

    time_t timer;
    time(&timer);
    char *message = ctime(&timer);
    bytes_sent=send(socket_client,message,strlen(message),0);
    printf("Sent %d of %d bytes.\n",bytes_sent,(int)strlen(message));

    printf("Closing connection.....\n");
    CLOSESOCKET(socket_client);
    printf("Closing listening socket.....\n");
    CLOSESOCKET(socket_listen);

    #if defined(_WIN32)
        WSACleanup();
    #endif
    printf("Finished....\n");
    return 0;
}