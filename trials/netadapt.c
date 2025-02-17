#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    struct ifaddrs *addresses;

    if(getifaddrs(&addresses)==-1){

        printf("No network adapters found\n");
        exit(1);
    }

    struct ifaddrs *address = addresses;

    while(address){

        int family=address->ifa_addr->sa_family;

        if(family==AF_INET || family==AF_INET6){

            printf("%s\t",address->ifa_name);
            printf("%s\n",family==AF_INET ? "IPV4" : "IPV6");

            char ap[100];
            const int family_size= family==AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(address->ifa_addr,family_size,
                        ap,sizeof(ap),0,0,NI_NUMERICHOST);
            printf("%s\n",ap);
        }

        address=address->ifa_next;
    }

    free(address);
    free(addresses);
    return 0;
}