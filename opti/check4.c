#include <stdio.h>
#include <stdlib.h>

void main(int argc,char **argv){
    FILE *Checkfile;
    int Byte;
    int Checksum;

    if(argc != 2){
        printf("Usage: ./a.out filename\n");
        exit(1);
    }

    if((Checkfile=fopen(argv[1],"rb")) == NULL){
        printf("Failed to open file.\n");
        exit(1);
    }
    Checksum=0;

    while((Byte=getc(Checkfile)) != EOF){
        Checksum += (unsigned int) Byte;
    }

    printf("Checksum value is %d\n",Checksum);
    exit(0);
}