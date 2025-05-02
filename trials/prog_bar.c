#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("Loading[");
    for(int i=0;i<20;i++){
        fflush(stdout);
        usleep(1000000);
        printf("#");
    }
    puts("] Done!");
    return 0;
}