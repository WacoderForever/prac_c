#include <stdio.h>
#include <time.h>

int main(){
    time_t timer;
    struct tm auto_tm;

    time(&timer);
    localtime_r(&timer,&auto_tm);
    printf("The time is %s\n",asctime(&auto_tm));
}