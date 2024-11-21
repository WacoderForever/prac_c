#include "allheaders.h"

void main(){
    int A[6]={12,134,-7,80,4564,756};

    for(int i=1;i<6;i++){
        int x=A[i];
        int j=i-1;

        while((j>-1) && (A[j] > x)){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=x;
    }
    for(int i=0;i<6;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
}