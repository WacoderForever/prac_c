#include "allheaders.h"

void merge(int arr[],int left,int mid,int right){
    int n1=mid-left+1;
    int n2=right-mid;
    int L[n1];
    int R[n2];

    for(int i=0;i<n1;i++){
        L[i]=arr[i];
    }
    for(int j=0;j<n2;i++){
        R[i]=arr[j];
    }

    i=0;
    j=0;
    k=left;
    while(i<n1 && j<n2){
        if(L[i]<R[j]){
            arr[k]=L[i];
            i++;
        }
        else{
            arr[k]=R[j];
            j++
        }
        k++;
    }
}

void MergeSort(int left,int right){
    int mid=left+(right-left)/2;
    
}
int main(){
    int A[]={67,98,1000,54,-90,75};
}