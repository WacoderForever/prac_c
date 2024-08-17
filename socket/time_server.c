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

}
