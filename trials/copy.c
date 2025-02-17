#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char buffer[2048];
void copy(int old,int new);

int main(int argc,char *argv[]){
    int fdnew,fdold;

    if(argc != 3){
        printf("Usage: copy source destination\n");
        exit(1);
    }
    fdold=open(argv[1],O_RDONLY);
    if(fdold == -1){
        printf("Failed to open source file.\n");
        exit(1);
    }
    fdnew=creat(argv[2],0666); //open in rw
    if(fdnew==-1){
        printf("Failed to create destination file.\n");
        exit(1);
    }
    copy(fdold,fdnew);
    printf("Copying complete.\n");
    return 0;
}

void copy(int old,int new){
    int count;
    while((count=read(old,buffer,sizeof(buffer)))>0){
        write(new,buffer,count);
    }
}