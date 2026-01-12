#include <stdio.h>
#include <time.h>

int main(){
    time_t largest=0x7fffffff;
    printf("Biggest=%s\n",asctime(gmtime(&largest)));
    printf("Size of time_t: %u\n",sizeof(time_t));
    return 0;
}