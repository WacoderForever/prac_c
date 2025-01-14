#include "apue.h"
#include <dirent.h>

int main(int argc,char* argv[]){
    DIR *dir;
    struct dirent *dirp;
    if(argc != 2){
        printf("Usage: ls filename.\n");
        exit(EXIT_FAILURE);
    }
    if((dir=opendir(argv[1]))==NULL){
        printf("Failed to open directory %s.\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    while((dirp=readdir(dir)) != NULL){
        printf("%s\n",dirp->d_name);
    }
    closedir(dir);
    return EXIT_SUCCESS;
}