#include <stdio.h>
#include <stdlib.h>

int main(){
    int A[]={43,67,12,34,9032,6789876};
    int size=sizeof(A)/4;
    int B[size];
    int smallest=A[0];
    int k=0;
    while(k<size-1){
    for(int i=k;i<size;i++){
        if(A[i]<smallest){
            smallest=A[i];
            int hold=A[k];
            A[k]=smallest;
            A[i]=hold;

        }
    }
    smallest=A[k+1];
    ++k;
    }
    for(int j=0;j<size;j++){
        printf("%d ",A[j]);
    }
    printf("\n");
}