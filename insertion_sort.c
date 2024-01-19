#include "allheaders.h"

int main(){
    int A[]={8,5,78,90,2,45,67};
    int size=sizeof(A)/4;
    int smallest=A[0];
    int k=0;
    while(k<size-1){
        for(int l=k;l<size;++l){
            if(A[l]<smallest){
                smallest=A[l];
                int hold=A[k];
                A[k]=smallest;
                A[l]=hold;
                smallest=A[l];

            }
        }
        printf("%d ",A[k]);
        k++;
    }
    

}