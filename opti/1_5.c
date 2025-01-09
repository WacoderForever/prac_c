#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 0x8000

int main(int argc,char* argv[]){
    int Handle;
    unsigned int Checksum;
    unsigned char *WorkingBuffer,*WorkingPtr;
    int WorkingLength,LengthCount;
    if(argc != 2){
        printf("Usage: ./a.out filename\n");
        exit(EXIT_FAILURE);
    }
    if((Handle=open(argv[1],O_RDONLY))==-1){
        printf("Failed to open file %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    //get memory for the buffer
    if((WorkingBuffer=malloc(BUFFER_SIZE))==NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    Checksum=0;
    do{
        if((WorkingLength=read(Handle,WorkingBuffer,BUFFER_SIZE))==-1){
            printf("Error reading file %s.\n",argv[1]);
            exit(EXIT_FAILURE);
        }
        WorkingPtr=WorkingBuffer;
        LengthCount=WorkingLength;
        while(LengthCount--){
            Checksum+=(unsigned int) *WorkingPtr++;
        }
    }while(WorkingLength);

    printf("Checksum : %u\n",Checksum);
    exit(EXIT_SUCCESS);
}