#include <stdio.h>
#include <stdlib.h>

void merge_sort(int Arr[],int left,int right){
    if (right <= left ) return ;
    int mid = left + (right - left)/2;
    merge_sort(Arr,left,mid);
    merge_sort(Arr,mid+1,right);
    int A[mid-left+1];
    int B[right-mid];
    for(int i=0;i<=mid-left;i++){
        A[i]=Arr[i];
    }
    int k=0;
    for(int i=mid-left+1;i<=right;i++){
        B[k]=Arr[i];
        k++;
    }
    int l=0;
    int n=0;
    for(int i=left;i<=right;i++){
        if(B[l] < A[n]) Arr[i] = B[l++];
        else Arr[i] = A[n++];
    }
}

void printArray(int *A, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n"); 
}

int main() {
    int A[] = {5, 6, 12, 7, -8, 790};
    int size = sizeof(A) / sizeof(A[0]); 
    printf("Initial array:\n");
    printArray(A, size);
    merge_sort(A,0,size-1);
    printf("Final array:\n");
    printArray(A, size);
    return 0;
}