#include "allheaders.h"

typedef struct {

    unsigned int a:2;
    unsigned int b:3;
    unsigned int c:1;


}bit_a;

int main(){

    bit_a bita_var;
    bita_var.a=3;

    printf("%d\n",bita_var.a);

    return 0;

}