#include "allheaders.h"

typedef union{

    struct{

        unsigned int a:2;
        unsigned int b:1;
        unsigned int c:3;
        unsigned int d:1;
        unsigned int e:1;

    };

    uint8_t data; //should be >= than the size of struct inorder to clear the whole struct

}union_a;


int main(){

    union_a union_bit;
    union_bit.data=0x00; //clear the whole bit field

    printf("a: %d\n",union_bit.a);
    
    union_bit.a=2;

    printf("a: %d\n",union_bit.a);
    

    return 0;
}