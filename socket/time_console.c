#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    time_t timer;
    time(&timer);

    printf("Local time is %s\n",ctime(&timer));

    return 0;
}