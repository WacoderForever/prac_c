#if defined (_WIN32)
#ifndef (_WIN32_WINNIT)
#define _WIN32_WINNIT 0x0600
#endif
#ifndef IPV6_V6ONLY
#define IPV6_V6ONLY 27
#endif
#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define GETSOCKETERRNO() (WSAGetLastError())
#define CLOSESOCKET(s) (closesocket(s))

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define SOCKET int
#define ISVALIDSOCKET(s) ((s) < 0)
#define GETSOCKETERRNO() (errno)
#define CLOSESOCKET(s) (close(s))

#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialize winsock api.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    #endif
    puts("Initialised socket API successfully.");

    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET6;
    hints.ai_socktype= SOCK_DGRAM;
    hints.ai_flags=AI_PASSIVE;
    
}