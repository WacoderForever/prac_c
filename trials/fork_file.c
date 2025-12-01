#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char **argv){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork() failed.");
        return 1;
    }

    if(pid == 0){
        execlp("./a.out","a.out",argv[1],argv[2],NULL);
        perror("execlp() failed"); // executed only if excelp() fails
        return 1;
    }
    else{
        wait((int *)0);
        printf("copy done\n");
    }
    return 0;
}