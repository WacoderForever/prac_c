#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600
#endif
#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif
#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define GETSOCKETERRNO() (WSAGetLastError())
#define CLOSESOCKET(s) (closesocket(s))

#else

#include <sys/socket.h>
#include <sys/types.h>
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

int main(){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise winsock api. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    #endif
    puts("Successfully initialised socket API");

    puts("Configuring local address......");
    struct addrinfo hints;
    hints.ai_family=AF_INET6;
    hints.ai_socktype=SOCK_DGRAM;
    hints.ai_flags=AI_PASSIVE;
    struct addrinfo *bind_address;
    if((getaddrinfo(NULL,"8080",&hints,&bind_address))<0){
        fprintf(stderr,"Failed to configure local address. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    puts("Creating socket.....");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"Failed to create socket. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    int option=0;
    if((setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,
        (void*)&option,(socklen_t)sizeof(option)))<0){
            fprintf(stderr,"setsockopt() failed. (%d)\n",GETSOCKETERRNO());
            return 1;
    }

    puts("Binding the socket to the local address.....");
    if((bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen))<0){
        fprintf(stderr,"Failed to bind socket to the address. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    struct sockaddr_storage client_addr;
    socklen_t client_len= sizeof(client_addr);
    char read[4096];
    int bytes_received=recvfrom(socket_listen,read,sizeof(read),0,(struct sockaddr*)&client_addr,&client_len);
    printf("Received(%d bytes): %.*s\n",bytes_received,bytes_received,read);

    puts("Remote address:");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo((struct sockaddr*)&client_addr,client_len,address_buffer,(socklen_t)sizeof(address_buffer),
                service_buffer,(socklen_t)sizeof(service_buffer),NI_NUMERICHOST | NI_NUMERICSERV);
    printf("Host: %s\n Service: %s\n",address_buffer,service_buffer);

    CLOSESOCKET(socket_listen);
    #if defined(_WIN32)
    WSACleanup();
    #endif

    puts("Finished");
    return 0;
}

