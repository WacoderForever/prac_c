#include "allheaders.h"

int main(){
    int token_num=0;
    char src[]="Hello,, world!";
    char *delimiters=" ,!";
    char *token=strtok(src,delimiters);

    while(token !=NULL){
        printf("%d: [%s]\n",++token_num,token);
        token=strtok(NULL,delimiters);
    }

    return 0;
}