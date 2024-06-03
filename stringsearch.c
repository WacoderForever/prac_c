#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char k[30];
    printf("Enter string to search:");
    fgets(k,30,stdin);
    char y='a';
    char z='p';
    if(strchr(k,y)){
        printf("Character %c is in the string %s\n",y,k);
    }
    else{
        printf("Character %c is not in the string %s\n",y,k);
    }
    if(strchr(k,z)){
        printf("Character %c is in the string %s\n",z,k);
    }
    else{
        printf("Character %c is not in the string %s\n",z,k);
    }
return 0;
}