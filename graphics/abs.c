#include <stdio.h>
#define CHAR_BIT 8

int main(){
    int v=45;
    printf("%d\n",v);
    int r; // result
    int mask = v >> (sizeof(int)*CHAR_BIT-1);

    r=(v+mask)^mask;
    printf("%d\n",r);
}