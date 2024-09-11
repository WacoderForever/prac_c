#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#if defined(_WIN32)
#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#define CLOSESOCKET(s) (closesocket(s))
#define GETSOCKETERRORNO() (WSAGetLAstError())
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#else
#define CLOSESOCKET(s) (close(s))
#define GETSOCKETERRORNO (errno)
#define ISVALIDSOCKET(s) (s>=0)
#define SOCKET int
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
