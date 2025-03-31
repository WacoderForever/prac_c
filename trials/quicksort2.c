#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp=*a;
    *b=*a;
    *a=temp;
}

void printArray(int A[],int size){
    for(int i=0;i<size;i++){
        printf("%d ",A[i]);
    }
    puts(""); 
}

int main(){
    int A[]={12,789,-906,768,546};
    int size=sizeof(A)/sizeof(int);
    printf("Initial Array:");
    printArray(A,size);
    quickSort(A,0,size-1);
    printf("Final Array:");
    printArray(A,size);
    return 0;
}