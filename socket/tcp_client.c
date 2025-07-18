#include "chap3.h"

#if defined(_WIN32)
#include <conio.h>
#endif

int main(int argc,char**argv){
    #if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialise winsock api.\n");
        return 1;
    }
    #endif

    if(argc < 3){
        fprintf(stderr,"Usage: a.out hostname port\n");
        return 1;
    }

    printf("Configuring remote address....\n");
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_socktype=SOCK_STREAM;
    struct addrinfo *peer_address;
    if(getaddrinfo(argv[1],argv[2],&hints,&peer_address)){
        fprintf(stderr,"Failed to get remote address.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    printf("Remote address is: \n");
    char address[100];
    char service[100];
    getnameinfo(peer_address->ai_addr,peer_address->ai_addrlen,
                address,(socklen_t)sizeof(address),
                service,(socklen_t)sizeof(service),NI_NUMERICHOST);
    printf("Address: %s\n",address);
    printf("Service: %s\n",service);

    printf("Creating socket.....\n");
    SOCKET socket_peer;
    socket_peer= socket(peer_address->ai_family,peer_address->ai_socktype,peer_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_peer)){
        fprintf(stderr,"socket() faied. (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    printf("Connecting to remote server....\n");
    if(connect(socket_peer,peer_address->ai_addr,peer_address->ai_addrlen)){
        fprintf(stderr,"connect() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(peer_address);

    printf("Connected....\n");
    printf("To send data enter text followed by enter:\n");

    while(1){
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer,&reads);
#if !defined(_WIN32)
        FD_SET(fileno(stdin),&reads);
#endif
        struct timeval timeout;
        timeout.tv_sec=0;
        timeout.tv_usec=100000;

        if(select(socket_peer+1,&reads,0,0,&timeout) < 0){
            fprintf(stderr,"select() failed.(%d)\n",GETSOCKETERRNO());
            return 1;
        }
        if(FD_ISSET(socket_peer,&reads)){
            char read[4096];
            int bytes_received = recv(socket_peer,read,4096,0);
            if(bytes_received < 1){
                printf("Connection closed by peer.\n");
                break;
            }
            printf("Received (%d bytes):%.*s\n",bytes_received,bytes_received,read);
        }
#if defined(_WIN32)
        if(_kbhit()){
#else   
        if(FD_ISSET(0,&reads)){
#endif
            char read[4096];
            if(!fgets(read,4096,stdin)) break;
            printf("Sending: %s",read);
            int bytes_sent = send(socket_peer,read,strlen(read),0);
            printf("sent: %d bytes\n",bytes_sent);
        }
    }

    printf("Closing socket......\n");
    CLOSESOCKET(socket_peer);

    #if defined(_WIN32)
        WSACleanup();
    #endif

    printf("Finished..\n");
    return 0;
}