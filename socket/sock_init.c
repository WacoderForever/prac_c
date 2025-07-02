#if defined(_WIN32)
#ifndef _WIN32_WINNT
//minimum windows version(Vista)
#define _WIN32_WINNT 0x0600 
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())

#else
//Unix platform
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

int main(){
    #if defined(_WIN32)
    WSADATA d; //winsock api data
    if(WSAStartup(MAKEWORD(2,2),&d)){ //MAKEWORD makes a 16-bit version number 2.2(most common and stable version)
        fprintf(stderr,"Failed to initialise winsock api");
        return 1;
    }
    #endif
    printf("Ready to use socket API\n");

    #if defined(_WIN32)
        WSACleanup();
    #endif

    return 0;
}