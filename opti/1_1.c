#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    int Handle;
    int Checksum;
    int ReadLength;
    unsigned char Byte;

    if(argc != 2){
        printf("Usage: ./a.out filename\n");
        exit(EXIT_FAILURE);
    }

    if((Handle=open(argv[1],O_RDONLY))<0){
        printf("Failed to open file: %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    Checksum=0;

    while((ReadLength=read(Handle,&(Byte),sizeof(Byte)))>0){
        Checksum += (unsigned int) Byte;
    }

    if(ReadLength == -1){
        printf("Failed to read file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Checksum is: %u\n",Checksum);
    return 0;

}