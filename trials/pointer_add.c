#include <stdio.h>
#include <stdlib.h>

int main(){
    int var[]={24,109,867};
    int *p=var;
    int d=0;
    int size=sizeof(var)/sizeof(var[0]);
    while(d<size){
        printf("Address of var[%d]:%p\tValue:%d\n",d,p,*p);
        d++;
        p++;
    }
    return 0;
}