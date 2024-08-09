#include "allheaders.h"

int main(){

    int A[]={8,5,78,90,2,45,67};
    int size=sizeof(A)/2;
    int B[size];
    int count=0;
    while(count<size){
        for(int i=0;i<size;i++){
            if(A[count]<B[i]){
                int hold=A[count];
                int hold2=B[i];
                //append left
                //move right
                for(int j=i;j<size;j++){
                    B[i]=hold;
                    hold3=
                    B[j+1]=hold2;

                }
            }

            if(A[count]>=B[i]){
                //append right
                //move right
            }
        }
    }
}