#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 0x8000

void main(int argc,char **argv){
    int Handle;
    unsigned char *WorkingBuffer,*WorkingPtr;
    int WorkingLength,LengthCount;
    unsigned int Checksum;

    if(argc != 2){
        printf("Usage: ./a.out filename.\n");
        exit(1);
    }

    if((Handle=open(argv[1],O_RDONLY))==-1){
        printf("Failed to open %s\n",argv[1]);
        exit(1);
    }
    //get memory to buffer the data internally
    if((WorkingBuffer=malloc(BUFFER_SIZE))==NULL){
        printf("Failed to allocate memory.\n");
        exit(1);
    }
    Checksum=0;
    do{
        if((WorkingLength=read(Handle,WorkingBuffer,BUFFER_SIZE))==-1){
            printf("Failed to read file.\n");
            exit(1);
        }
        LengthCount=WorkingLength;
        WorkingPtr=WorkingBuffer;

        while(LengthCount--){
            //add each byte into the checksum
            Checksum += (unsigned int) *WorkingPtr++;
        }

    }while(WorkingLength);

    printf("Checksum is: %d\n",Checksum);
    exit(0);
}