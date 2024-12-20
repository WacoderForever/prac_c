#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

extern int Checksum(int Handle,unsigned int *checksum_value,unsigned char Byte);

void main(int argc,char **argv){
    int Handle;
    unsigned char Byte;
    unsigned int Readlength;
    unsigned int checksum_value=0;
    if(argc != 2){
        printf("Usage: ./a.out filename\n");
        exit(1);
    }
    if((Handle=open(argv[1],O_RDONLY)) == -1){
        printf("Failed to open file.\n");
        exit(1);
    }
    if(Checksum(Handle,&checksum_value,Byte)==0){
        printf("Failed to read file.\n");
        exit(1);
    }
    close(Handle);
    printf("Checksum: %d\n",checksum_value);
    exit(0);
}