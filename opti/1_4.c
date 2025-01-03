#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    FILE *CheckFile;
    int Byte;
    unsigned int Checksum;

    if(argc != 2){
        puts("Usage: ./a.out filename");
        exit(1);
    }

    if((CheckFile=fopen(argv[1],"rb"))==NULL){
        printf("Failed to open file: %s\n",argv[1]);
        exit(1);
    }

    Checksum=0;

    while((Byte=getc(CheckFile)) != EOF){
        Checksum += (unsigned int)Byte;
    }

    printf("The checksum is : %u\n",Checksum);

    return 0;
}