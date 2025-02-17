#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

extern int ChecksumFile(int Handle, unsigned int *Checksum);

int main(int argc,char *argv[]){
    int Handle;
    unsigned int Checksum;
    unsigned char Byte;
    int ReadLength;

    if(argc != 2){
        puts("Usage: ./a.out filename");
        exit(EXIT_FAILURE);
    }

    if((Handle=open(argv[1],O_RDONLY))<0){
        printf("Failed to open file %s",argv[1]);
        exit(EXIT_FAILURE);
    }

    if(!ChecksumFile(Handle,&Checksum)){
        puts("Failed to get the checksum");
        exit(EXIT_FAILURE);
    }

    printf("Checksum: %u\n",Checksum);
    return 0;
}