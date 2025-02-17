#include <stdio.h>
#include <time.h>

int main(){
    time_t timer;
    time(&timer);
    printf("The time is %s\n",asctime(localtime(&timer)));
}