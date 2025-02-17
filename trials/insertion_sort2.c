#include "allheaders.h"
void insertion_sort(int A[],int n){
    for(int i=1;i<=n;i++){
        int x=A[i];
        int j=i-1;
        while((j>=0) &&(A[j]>x)){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=x;
    }
}
void main(){
 
}