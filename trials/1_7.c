#include "apue.h"
#include <sys/wait.h>

int main(){
    char buf[MAXLINE]; /*from apue.h*/
    pid_t pid;
    int status;
    printf("%% ");  /*print % */
    while((fgets(buf,MAXLINE,stdin)) != NULL){
        if(buf[strlen(buf)-1]=='\n'){
            buf[strlen(buf)-1]=0;
        }
        if((pid=fork()) < 0 ){
            printf("fork() error\n");
        }
        else if(pid==0){    //child process
            if(execlp(buf,buf,(char*)0) < 0){
                perror("execlp() error");
                exit(127);
            }
        }
        //parent
        if((pid=waitpid(pid,&status,0)) < 0){
            printf("waitpid error\n");
        }
        printf("%% ");
    }
}