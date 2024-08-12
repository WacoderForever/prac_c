#include "allheaders.h"

int main(){

    int A[]={8,5,78,90,2,45,67};
    int size=sizeof(A)/2;
    int B[size];
    B[0]=A[0];
    int count=0;
    while(count<size){

        if(A[count+1]<B[count]){
            int C[size-count];
            for(int i=0;i<=count;i++){
                C[i]=B[];
            }
        }
        count++;
    }
}