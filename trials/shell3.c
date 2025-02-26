#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define DELIM " \t\r\a\n"
#define MAX_ARGS 64

typedef struct{
    char *name;
    char **args;
    char num_args;
}Command;

char *read_input(void);
int parse_line(char *line,Command *cmd);
int execute_command(Command *cmd);
void free_cmd(Command *cmd);

int main(){
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

char *read_input(void){
    char *input=NULL;
    size_t buf_size=0;
    if(getline(&input,&buf_size,stdin)==-1){
        if(feof(stdin)){
            //end of input stream
            exit(0);
        }
        perror("read_input");
    }
    return input;
}

int parse_line(char *line,Command *cmd){
    size_t buf_size=MAX_ARGS;
    int position=0;
    char **tokens=(char**)malloc(buf_size*sizeof(char*));
    char *token;
    if(!token){
        printf("Failed to allocate memory\n");
    }
    token=strtok(line,DELIM);
    while(token != NULL){
        tokens[position++]=token;
        if(position >= buf_size){
            buf_size += MAX_ARGS;
            tokens=(char**)realloc(tokens,buf_size*sizeof(char*));
            if(!tokens){
                fprintf(stderr,"Failed to allocate memory\n");
                exit(1);
            }
        }
        token=strtok(line,NULL);
    }
    cmd->name=tokens[0];
    cmd->args=tokens;
    cmd->num_args=position;

    return 1;
}

int execute_command(Command *cmd){
    pid_t pid;
    pid=fork();
    if(pid < 0){
        fprintf(stderr,"fork() failed\n");
        exit(1);
    }
    if (pid == 0) execvp(cmd->name,cmd->args);
    int status;
    do{
        waitpid(pid,&status,WUNTRACED);
    }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    return 1;
}

void free_cmd(Command *cmd){
    free(cmd->args);
}