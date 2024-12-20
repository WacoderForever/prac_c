
//including the neccesary header files
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    struct ifaddrs *addresses; //stores addresses 

    if(getifaddrs(&addresses)==-1){ //getifaddrs() gets the addresses and stores them in a linked list on fail return -1 else 0

        printf("Failed to get the adddresses\n");
        exit(1);
    }

    struct ifaddrs *address=addresses; //address to loop through the linked list

    while(address){

        int family=address->ifa_addr->sa_family;

        if(family==AF_INET || family==AF_INET6){

            printf("%s\t",address->ifa_name);
            printf("%s\t",family==AF_INET ? "IPV4" : "IPV6");

            char ap[100]; //buffer to store textual address
            int family_size=family==AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            //storing the textual address to ap
            getnameinfo(address->ifa_addr,family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            printf("\t%s\n", ap);
        }

        address=address->ifa_next;

    }
    //freeing memory 
    freeifaddrs(addresses);

    return 0;

}