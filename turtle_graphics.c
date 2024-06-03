#include "allheaders.h"

int rowpos=0;
int columnpos=0;

void Move(int array[50][50],unsigned int steps,int pos,int penup){

    if(pos==0){
        for(int i=0;i<steps-1;i++){
            if(penup==2){
                array[rowpos][columnpos]=1;
                --rowpos;
            }
            else{
                --rowpos;
            }
        }
    }

    if(pos==1){
        for(int i=0;i<steps-1;i++){
            if(penup==2){
                array[rowpos][columnpos]=1;
                ++columnpos;
            }
            else{
                ++columnpos;
            }
        }
    }

    if(pos==2){
        for(int i=0;i<steps-1;i++){
            if(penup==2){
                array[rowpos][columnpos]=1;
                ++rowpos;
            }
            else{
                ++rowpos;
            }
        }
    }

    if(pos==3){
        for(int i=0;i<steps-1;i++){
            if(penup==2){
                array[rowpos][columnpos]=1;
                --columnpos;
            }
            else{
                --columnpos;
            }
        }
    }
}

void PrintArray(int array[50][50]){

    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            if(array[i][j]==1){
                printf("X");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}

int TurnRight(int currentpos){

    int finalpos=0;
    if(currentpos==0) finalpos=1;
    if(currentpos==1) finalpos=2;
    if(currentpos==2) finalpos=3;
    if(currentpos==3) finalpos=0;

    return finalpos;
}

int TurnLeft(int currentpos){

    int finalpos=0;
    if(currentpos==0) finalpos=3;
    if(currentpos==1) finalpos=0;
    if(currentpos==2) finalpos=1;
    if(currentpos==3) finalpos=2;

    return finalpos;
}
int GetSteps(char *command){

    char *token;
    int number;

    // tokenise string using comma
    token = strtok(command, ",");
    // Iterate through tokens
    while (token != NULL) {
        // Check if the token is after the comma
        if (token != command) {
            // Convert the token to an integer
            number = atoi(token);
            break;
        }
        token = strtok(NULL, ",");
    }

    return number;
}

int main(){

    char *command=NULL;
    size_t size=0;
    printf("Enter command: ");
    getline(&command,&size,stdin);
    command[(strcspn(command,"\n"))]=0;

    int array[50][50]={0};
    int penup=1;
    int pos=1;

    while(strcmp(command,"9")){

        if(!strcmp(command,"1")){

            penup=1;
        }

        if(!strcmp(command,"2")){

            penup=2;
        }

        if(!strcmp(command,"3")){

            pos=TurnRight(pos);
        }

        if(!strcmp(command,"4")){

            pos=TurnLeft(pos);
        }

        if(command[0]=='5'){

            int steps=GetSteps(command);
            Move(array,steps,pos,penup);
        }

        if(!strcmp(command,"6")){

            Move(array,2,pos,penup);
            PrintArray(array);
        }

        printf("Enter command: ");
        getline(&command,&size,stdin);
        command[(strcspn(command,"\n"))]=0;
    }

    return 0;
}