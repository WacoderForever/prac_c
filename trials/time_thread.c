#include <stdio.h>
#include <time.h>

int main(){
    time_t timer;
    struct tm auto_tm;
    time(&timer);
    localtime_r(&timer,&auto_tm);

    printf("The current time: %s",asctime(&auto_tm));
    return 0;
}