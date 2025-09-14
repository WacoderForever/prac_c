#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char *str,char *part,int index){
    int len=strlen(part);
    int i=0;
    while(i<len){
        if(str[index++] != part[i++]) return 0;
    }
    return 1;
}

int main(){
    char *str="bbabaxababay";
    char *part="aba";
    int res=0;
    for(int i=0; str[i] != '\0';i++){
        if(str[i]=='a'){
            if(match(str,part,i)) res++;
        }
    }
    printf("There are %d patterns of %s in the string %s\n",res,part,str);
}