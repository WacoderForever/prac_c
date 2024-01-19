#include <stdio.h>
#include <ctype.h>
void Toupper(char str[]){
    while (*str !='\0'){
        *str=toupper(*str);
        ++str;
    }
}
int main(){
    char str[]="cGFgjGGFFkghgkh H";
    printf("String before modifying:%s\n",str);
    Toupper(str);
    printf("String after formatting:%s\n",str);
}