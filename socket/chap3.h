#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#pragma comment(lib,"ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

#define GETSOCKETERRNO() WSAGetLastError()
#define ISVALIDSOCKET(s) (s != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h> 


#define SOCKET int
#define GETSOCKETERRNO() (errno)
#define ISVALIDSOCKET(s) (s >= 0)
#define CLOSESOCKET(s) close(s)

#endif

#include <stdio.h>
#include <string.h>


