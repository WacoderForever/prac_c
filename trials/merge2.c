#include <stdio.h>
#include <stdlib.h>

void merge(int arr[],int left,int mid,int right){
    int n1=mid-left+1;
    int n2=right-mid;
    int A[n1];
    int B[n2];

    for(int i=0;i<n1;i++) A[i] = arr[left+i];
    for(int j=0;j<n2;j++) B[j] = arr[mid+1+j];

    int i=0;
    int j=0;
    int k=left;
    while(i<n1 && j<n2){
        if(B[j]<A[i]) arr[k++] = B[j++];
        else arr[k++]=A[i++];
    }

    //copy remaining elements
    while(i<n1) arr[k++] = A[i++];
    while(j<n2) arr[k++] = B[j++];
}

void merge_sort(int arr[],int left,int right){
    if(right <= left) return;
    int mid = left +(right - left)/2;
    merge_sort(arr,left,mid);
    merge_sort(arr,mid+1,right);
    merge(arr,left,mid,right);
}

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n"); 
}

int main() {
    int A[] = {789,905,-98,056};
    int size = sizeof(A) / sizeof(A[0]); 
    printf("Initial array:\n");
    printArray(A, size);
    merge_sort(A,0,size-1);
    printf("Final sorted array:\n");
    printArray(A, size);
    return 0;
}