#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){

    int temp=*a;
    *a=*b;
    *b=temp;
}

void selectionSort(int arr[],int n){
    for(int i=0;i<=n-1;i++){
        int minindex=i;
        for(int j=i+1;j<=n-1;j++){
            if(arr[j]<arr[minindex]) minindex=j;
        }
        swap(&arr[i],&arr[minindex]);
    }
}
void printArray(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
        if(i+1<n) printf(", ");
    }
    printf("\n");
}
int main(){
    int A[]={123,56,78,16,90,-10};
    printArray(A,6);
    selectionSort(A,6);
    printArray(A,6);
}