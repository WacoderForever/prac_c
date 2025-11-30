#include <stdio.h>
#include <unistd.h>

int main(){
    printf("I am the process with id-%d\n",getpid());
    return 0;
}