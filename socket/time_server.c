#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#endif

//macro to abstract difference between Berkely and WinSock sockets

#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())

#else
#define ISVALIDSOCKET(s) (s >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#endif

#include <stdio.h>
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

    //local address for the server to bind to
    printf("Configuring local address....\n");
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flag=AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(NULL,"8080",&hint,&bind_address);

    //creating socket
    printf("Creating socket.....\n");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"socket() failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    //bind socket to the local address
    printf("Binding the socket to the local address.....\n");
    if(bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen)){
        fprintf(stderr,"bind() failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    //making the socket to listen for connections
    if((listen(socket_listen,10)<0)){
        fprintf(stderr,"listen() failed. (%d). \n",GETSOCKETERRNO());
        return 1;
    }

    //accepting incoming connections
    printf("Waiting for connection.......\n");
    struct sockadrr_storage client_address;
    socklen_t client_len=sizeof(client_address);
    SOCKET socket_client=accept(socket_listen,(struct sockaddr*) &client_address,&client_len);
    if(!ISVALIDSOCKET(socket_client)){
        fprintf(stderr,"accept() failed. (%d).\n",GETSOCKETERRNO());
        return 1;
    }

    //printing clients address info
    printf("Printing clients info....\n");
    char addressbuffer[1000];
    getnameinfo((struct sockaddr*) &client_address,client_len,addressbuffer,sizeof(addressbuffer),NI_NUMERICHOST);
    printf("%s\n",addressbuffer);
    
}
