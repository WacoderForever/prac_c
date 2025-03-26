#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp=*a;
    *b=*a;
    *a=temp;
}

int partition(int arr[],int low,int high){
    int pivot=arr[low];
    int k=low;
    for(int i=low+1;i<=high;i++){
        if(arr[i]<arr[k]){
            swap(&arr[i],&arr[k]);
            k++;
        }
    }
    return k;
}

void quickSort(int arr[],int low,int high){
    if(low<=high){
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi);
        quickSort(arr,pi+1,high);
    }
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