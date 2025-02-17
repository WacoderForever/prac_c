#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

typedef struct{
    char *name;
    char **args;
    char num_args;
}Command;

char *read_line(void);
int parse_line(char* line,Command* cmd);
int execute_command(Command *cmd);
void free_cmd(Command* cmd);

int main(int argc,char **argv){
    char *text=NULL;
    Command cmd;
    int status=1;
    while(status){
        printf("%% ");
        text=read_line();
        if(parse_line(text,&cmd)){
            status=execute_command(&cmd);
            (void)free_cmd(&cmd);
        }

    }
    free(text);
    return 0;
}

char* read_line(void){
    char *line=NULL;
    size_t buff_size=0;
    if(getline(&line,&buff_size,stdin)==-1){
        if(feof(stdin)){
            //end of file or CTRL+D
            exit(0);
        }
        perror("read_line");
        exit(1);
    }
    return line;
}

int parse_line(char* line,Command *cmd){
    int buff_size=MAX_ARGS;
    int position=0;
    char **tokens=(char**)malloc(buff_size*sizeof(char*));
    char *token;
    if(!token){
        fprintf(stderr,"Allocation failed.\n");
        exit(1);
    }
    token=strtok(line,DELIM);
    while(token != NULL){
        tokens[position++]=token;
        if(position >= buff_size){
            buff_size += MAX_ARGS;
            tokens=(char **)realloc(tokens,buff_size*sizeof(char*));
            if(!tokens){
                fprintf(stderr,"Allocation failed.\n");
                exit(1);
            }
        }

        token=strtok(NULL,DELIM);
    }
    tokens[position]=NULL;
    if(position==0){
        free(tokens);
        exit(0);
    }
    cmd->args=tokens;
    cmd->num_args=position;
    cmd->name=tokens[0];
    return 1;
}

int execute_command(Command *cmd){
    pid_t pid;
    if(!strcmp(cmd->name,"exit"))   return 0;
    pid=fork();
    if(pid < 0){
        fprintf(stderr,"fork() failed.\n");
        exit(1);
    }
    if(pid == 0) execvp(cmd->name,cmd->args); //child process
    int status;
    do{
        (void)waitpid(pid,&status,WUNTRACED);
    }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    return 1;
}

void free_cmd(Command *cmd){
    free(cmd->args);
}