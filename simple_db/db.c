#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma pack(1) 

typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer=(InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer=NULL;
    input_buffer->buffer_length=0;
    input_buffer->input_length=0;

    return input_buffer;
}

void print_prompt(){printf("db > ");}
void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read=getline(&(input_buffer->buffer),&(input_buffer->buffer_length),stdin);

    if(bytes_read < 0){
        puts("Error reading input.");
        exit(EXIT_FAILURE);
    }

    //ignore trailing newline
    input_buffer->input_length=bytes_read-1;
    input_buffer->buffer[bytes_read-1]=0;
}

void close_input_buffer(InputBuffer *input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

typedef enum{
    META_SUCCESS,
    META_COMMAND_UNRECOGNISED_COMMAND
}MetaCommandResult;

typedef enum{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT
}PrepareResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer){
    if(!strcmp(input_buffer->buffer,".exit")){
        exit(EXIT_SUCCESS);
    }
    else{
        return META_COMMAND_UNRECOGNISED_COMMAND;
    }
}

typedef enum{
    STATEMENT_INSERT,
    STATEMENT_SELECT
}StatementType;

typedef struct{
    StatementType type;
}Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer,Statement *statement){
    if(!strncmp(input_buffer->buffer,"insert",6)){
        statement->type=STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if(!strcmp(input_buffer->buffer,"select")){
        statement->type=STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNISED_STATEMENT;
}

void execute_statement(Statement* statement){
    switch(statement->type){
        case STATEMENT_INSERT:
            printf("This is where we perform an insert.\n");
            break;
        case STATEMENT_SELECT:
            printf("This is where we perform a select.\n");
            break;
    }
}

int main(int argc,char* argv[]){
    InputBuffer* input_buffer=new_input_buffer();
    while(true){
        print_prompt();
        read_input(input_buffer);

        if(input_buffer->buffer[0]=='.'){
            switch(do_meta_command(input_buffer)){
                case META_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNISED_COMMAND:
                    printf("Unrecognised command: %s\n",input_buffer->buffer);
                    continue;
            }
        }
        Statement statement;
        switch(prepare_statement(input_buffer,&statement)){
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNISED_STATEMENT:
                printf("Unrecognised statement %s\n",input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("Executed\n");
    }
}