#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rev(const char* const strp){
    if('\0'==strp[0]){
        return;
    }
    else{
        rev(&strp[1]);
        putchar(strp[0]);
    }
}
int main(){
    char sent[30];
    printf("Enter new line of character:");
    //read string
    fgets(sent,30,stdin);
    printf("The string in reversed format:");
    rev(sent);
    puts(" ");
}