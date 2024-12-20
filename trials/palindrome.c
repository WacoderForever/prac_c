#include <stdio.h>
#include <string.h>
void revstr(char *str){
    if ('\0'==str[0]){
        return;
    }
    else{
        revstr(&str[1]);
        putchar(str[0]);
    }
   
}
int main(){
    char *str="radar";
    char *rev;
    sscanf(rev,"%s",revstr(str));
    if(!strcmp(str,rev)){
        printf("The string is a palindrome.");
    }
    else{
        printf("The string is not a palindrome.");
    }
}