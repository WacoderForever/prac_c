#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#endif

#if defined(_WIN32)
#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif
#define CLOSESOCKET(s) (closesocket(s))
#define GETSOCKETERRNO() (WSAGetLastError())
#define ISVALIDSOCKET(s) (s != INVALID_SOCKET)
#else
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#define CLOSESOCKET(s) (close(s))
#define ISVALIDSOCKET(s) (s>=0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
