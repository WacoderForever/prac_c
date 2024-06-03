#include <stdio.h>
#include <stdlib.h>

int main(){
    int a[10]={10,23,32,45,56,78,89,90,120};
    int n;
    printf("Enter integer to search for:");
    scanf("%d",&n);
    int low,high,mid;
    low=0;
    high=9;
    mid=(low+high)/2;
    while((n!=a[mid])&&(low<=high)){
        if(a[mid]>n){
            high=mid-1;
            mid=(low+high)/2;
            for(int i=low;i<high;i++){
                printf("%d ",a[i]);
            }
            puts("");
        }
        if(a[mid]<n){
            low=mid+1;
            mid=(low+high)/2;
            for(int i=low;i<high;i++){
                printf("%d ",a[i]);
            }
            puts("");
        }
        else{
        if(a[mid]==n){
            printf("%d is in the array",n);
        }
        else{
            printf("%d is not in the array",n);
        }
        }
       
    }

}