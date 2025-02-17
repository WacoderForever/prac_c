#include "allheaders.h"

void insert_inv(int A[],int n){
    for(int i=1;i<n;i++){
        int temp=A[i];
        int j=i-1;
        while((j>=0) && (temp>A[j])){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=temp;
    }
}
void printarray(int A[],int n){
    for(int i=0;i<n;i++){
        printf("%d, ",A[i]);
    }
    printf("\n");
}
int main(){
    int A[]={7,2,9,3,5,10};
    printarray(A,6);
    insert_inv(A,6);
    printarray(A,6);
    return 0;
}