#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int partition(int arr[],int low,int high){
    int pivot=arr[high];
    int i=low-1;
    for(j=low;j<=high-1;j++){
        if(arr[j]<pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return (i+1);
}

void quickSort(int arr[],int low,int high){

    if(low<high){
        int pi=partition(arr,low,high);
        quickSort(arr,low,p-1);
        quickSort(arr,p+1,high);

    }
}