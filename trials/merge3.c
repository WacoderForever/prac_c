#include <stdio.h>
#include <stdlib.h>

void merge(int *A,int left,int fT,int sT,int right){
    int n1=fT-left+1;
    int n2=sT-fT;
    int n3=right-sT;
    int B[n1];
    int C[n2];
    int D[n3];
    int i=0;
    int j=0;
    int k=0;
    while(i<n1) B[i++]=A[left+i];
    while(j<n2) C[j++]=A[left+i+j];
    while(k<n3) D[k++]=A[left+i+j+k];
    i=0;
    j=0;
    k=0;
    int l=left;
    while((i<n1) && (j<n2) && (k<n3)){
        if(B[i] <= C[j]){
            if(B[i] <= D[k]) A[l++] = B[i++]; //B is smallest
            else A[l++] = D[k++]; //D is smallest
        }
        if(C[j] < B[i]){
            if(C[j] <= D[k]) A[l++] = C[j++]; //C is smallest
            else A[l++] = D[k++]; //D is smallest

        }
    }

    if(i==n1){ //exhausted array B
        while((j < n2) && (k < n2)){
            if(C[j] < D[k]) A[l++] = C[j++];
            else A[l++] = D[k++];
        }
    }
    if(j==n2){ //exhausted array C
        while((i < n1) && (k < n3)){
            if(B[i] < D[k]) A[l++] = B[i++];
            else A[l++] = D[k++];
        }
    }
    if(k==n3){ //exhausted array D
        while((i<n1) && (j<n2)){
            if(B[i] < C[j]) A[l++] = B[i++];
            else A[l++] = C[j++];
        }
    }
    //copy remaining elements
    while(i<n1) A[l++] = B[i++];
    while(j<n2) A[l++] = C[j++];
    while(k<n3) A[l++] = D[k++];
}

void merge_sort(int *A,int left,int right){
    if(right <= left) return;
    int fT=left + (right-left)/3;
    int sT=(left + (right-left)/3)*2;
    merge_sort(A,left,fT);
    merge_sort(A,fT,sT);
    merge_sort(A,sT,right);

    merge(A,left,fT,sT,right);

}

void printArray(int *A, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *A);
        A++;
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