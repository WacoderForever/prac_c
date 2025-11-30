#include <stdio.h>

void fooi(int x){
    printf("Int: %d\n",x);
}

void foof(float x){
    printf("Float: %f\n",x);
}

#define foo(x) _Generic(x,\
    int: fooi(x),\
    float: foof(x)\
)
int main(){
    foo(69);
    foo(65.98768f);
    return 0;
}