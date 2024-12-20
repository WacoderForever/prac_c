#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 0x8000

extern void Checksum_Chunk(unsigned char *WorkBuffer,int WorkingLength,int *checksum);

void main(int argc,char **argv){
    int Handle;
    unsigned char *WorkBuffer;
    int WorkingLength;
    int checksum;

    if(argc != 2){
        printf("Usage:./a.out filename\n");
        exit(1);
    }

    if((Handle=open(argv[1],O_RDONLY))==-1){
        printf("Failed to open %s\n",argv[1]);
        exit(1);
    }
    //allocate memory to buffer data internally
    if((WorkBuffer=malloc(BUFFER_SIZE))==NULL){
        printf("Failed to allocate memory\n");
        exit(1);
    }
    checksum=0;
    do{
        if((WorkingLength=read(Handle,WorkBuffer,BUFFER_SIZE))==-1){
            printf("Failed to read file.\n");
            exit(1);
        }
        if(WorkingLength){
            Checksum_Chunk(WorkBuffer,WorkingLength,&checksum);
        }

    }while(WorkingLength);

    printf("Checksum: %d\n",checksum);
    exit(0);
}