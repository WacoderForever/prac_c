#include "chap3.h"

#if defined(_WIN32)
#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif
#endif


#include <ctype.h>

int main(){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise winsock2 api.\n");
        return 1;
    }
    #endif
    printf("Socket API initialised successfully");

    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET6;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    struct addrinfo *bind_address;
    getaddrinfo(0,"8088",&hints,&bind_address);

    printf("Creating socket......\n");
    SOCKET socket_listen;
    socket_listen=socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr,"socket() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    int option=0;
    if((setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,
                    (const void *)option,(socklen_t)sizeof(option)))<1){
        fprintf(stderr,"setsockopt() failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    printf("Binding the socket to the local address.\n");
    if(bind(socket_listen,bind_address->ai_addr,bind_address->ai_addrlen)){
        fprintf(stderr,"bind() failed. (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    if(listen(socket_listen,10)<0){
        fprintf(stderr,"listen() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen,&master);
    SOCKET max_socket = socket_listen;

    printf("Waiting for connections....\n");
    while(1){
        fd_set reads;
        reads=master;
        if(select((max_socket+1),&reads,0,0,0)<0){
            fprintf(stderr,"select() falied. (%d)\n",GETSOCKETERRNO());
            return 1;
        }
        SOCKET i;
        for(i=1;i<=max_socket;i++){
            if(FD_ISSET(i,&reads)){
                if(i==socket_listen){
                    
                }
            }
        }
    }
}