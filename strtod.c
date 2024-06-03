#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){
    char *str="523.56 is a real  number 8903.5 and 7680.2";
    char *strp;
    int count=0;
    int size=4;
    while(*str!='\0'){
        char *k;
        strcpy(k,str);
        printf("Double value:%.2f\n",strtod(k,&strp));
        strcpy(str,strp);
        char *j;
        strcpy(strp,j);
        //find length of string
        

    }
return 0;
}