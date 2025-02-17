#include "allheaders.h"

int findint(int A[],int x){
    int j=-1;
    int left=0;
    int right=14;

    while((j == -1) && (left <= right)){
        int mid=(int)((left+right)/2);
        if(x==A[mid]) j=mid;
        else if(x < A[mid]) right=mid-1;
        else left=mid+1;
    }
    return j;
}
void main(){
    int A[14] ={1,4,5,7,8,9,10,12,15,22,23,27,32,35};
    int x;
    printf("Enter integer to search:");
    scanf("%d",&x);
    int index=findint(A,x);
    index==-1 ? printf("Integer not in array\n") : printf("Integer is on index %d\n",findint(A,x));
}