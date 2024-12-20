#include <stdio.h>

void display(unsigned int value);
int main(){
    int value;
    printf("Enter value to convert to binary equivalent:");
    scanf("%d",&value);
    display(value);
}
void display(unsigned int value){
    unsigned int mask=1<<31;
    for(int i=1;i<=32;i++){
        putchar(value & mask ?'1':'0');
        value=value<<1;
        if(i%8==0){
            putchar(' ');
        }
    }
    putchar('\n');
}