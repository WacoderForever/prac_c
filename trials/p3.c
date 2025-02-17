#include <stdio.h>
#include <stdlib.h>

int main(){
    int num=10;
    int *p=&num;
    printf("Value of num: %d\n",num);
    printf("%d\n",*p);
    *p=200;
    printf("Value of num: %d\n",num);
    printf("%d\n",*p);

}