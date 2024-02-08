#include "allheaders.h"

int main(){
    char src[]="1.2,3.5,4.6,8.19";
    char *next=NULL;
    char *first=strtok_r(src,",",&next);

    do{
        char *part;
        char *posn;

        printf("%s\n",first);
        part=strtok_r(first,".", &posn);

        while(part != NULL){

            printf("%s\n",part);
            part=strtok_r(NULL,".",&posn);
        }


    }
    while((first=strtok_r(NULL,",",&next)) != NULL);


    return 0;
}