#include <stdio.h>
#include <stdlib.h>

int main(){
    int var = 42;
    int *intPtr;        //pointer to an integer
    char *charPtr;      //pointer to character
    float *floatPtr;    //pointer to float

    intPtr = &var;

    int value = *intPtr;
    printf("Value = %d\n",value);
    *intPtr = 100;
    printf("var = %d\n",var);

    void *genericPtr;   //generic pointer
    genericPtr = &value;
    printf("Value = %d\n",*((int *)genericPtr));

    char k= 'K';
    genericPtr = &k;
    printf("k = %c\n",*((char*)genericPtr));
    return 0;
}