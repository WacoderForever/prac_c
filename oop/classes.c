#include <stdio.h>

typedef struct C{
    int a;
    int b;
    void (*add)(struct C*);
}C;

void add_and_print(struct C* demo){
    int ans = demo->a + demo->b;
    printf("Sum of %d and % d is %d\n",demo->a,demo->b,ans);
}

int main(){
    struct C k = {.a=10, .b=20, .add=add_and_print};
    k.add(&k);
}