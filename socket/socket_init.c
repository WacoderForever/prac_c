#if defined(_WIN32)
#ifndef _WIN32_WINNIT
#define _WIN32_WINNIT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#endif

int main(){
   #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise.\n");
        return 1;
    }
    #endif
    printf("Socket initialised.\n");

    #if defined(_WIN32)
        WSACleanup();
    #endif
    return 0;
}