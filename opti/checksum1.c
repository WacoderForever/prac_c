#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc,char* argv[]){
    int Handle;
    unsigned char Byte;
    unsigned int Checksum;
    int Readlength;

    if(argc != 2){
        printf("Usage: checksum filename\n");
        exit(1);
    }

    if((Handle=open(argv[1],O_RDONLY))==-1){
        printf("Failed to open file: %s\n",argv[1]);
        exit(1);
    }

    Checksum=0;

    while((Readlength=read(Handle,&Byte,sizeof(Byte)))>0){
        Checksum += (unsigned int)Byte;
    }
    printf("The checksum is %d\n",Checksum);
    exit(0);
}