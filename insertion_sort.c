#include "allheaders.h"

int main(){

    int a[]={1,2,3,4,5,6,7};
    int size=sizeof(a)/4;
    int b[size];
    b[0]=a[0];
    int count=1;

    while(count<size){
        if(a[count]<b[0]){
            int c[count];
            for(int i=0;i<count;i++){
                c[i]=b[i];
            }
            b[0]=a[count];
            for(int i=1;i<=count;i++){
                b[i]=c[i-1];
            }
        }
        if(a[count]>=b[count-1]){
            b[count]=a[count];
        }
        count++;
    }

    for(int i=0;i<size;i++){
        printf("%d, ",b[i]);
    }
    printf("\n");
}