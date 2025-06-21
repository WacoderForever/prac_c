#include <stdio.h>

#define CHAR_BIT 8

int main(){
    int v=-45;
    int sign;
    
    sign=-(int) ((unsigned int)v >> (sizeof(int)*CHAR_BIT-1));
    printf("%d\n",sign);

    return 0;
}