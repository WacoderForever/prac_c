#include <stdio.h>

int main(){
    int a[10]={[2 ... 7]=99,[8]=74};
    for(int i=0;i<10;i++){
        printf("arr[%d]=%d\n",i,a[i]);
    }
}