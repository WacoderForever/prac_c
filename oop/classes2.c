#include <stdio.h>
#include <stdlib.h>

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
    struct C *k = (struct C*)malloc(sizeof(struct C));
    k->a = 10;
    k->b = 20;
    k->add = add_and_print;  
    k->add(k);
    free(k);
}