#include "allheaders.h"

int main(){
   int A[]={12,134,-7,80,4564,756};
   int size=sizeof(A)/sizeof(A[0]);
   int B[size];
   B[0]=A[0];
   int count=1;
   while(count<size){
    int j=count-1;
    int temp=A[count];

    while((j>=0) && (B[j]>temp)){
        B[j+1]=B[j];
        j--;
    }
    B[j+1]=temp;
    count++;
   } 
   for(int i=0;i<size;i++){
    printf("%d,",B[i]);
   }
   printf("\n");
   return 0;
}
