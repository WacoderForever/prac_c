#define _GNU_SOURCE
#include <stdio.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv){

    printf("Thread id: %ld\n",syscall(SYS_gettid));
    /* You can also use __NR_gettid*/
    return 0;
}
