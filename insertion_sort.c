#include "allheaders.h"

int main(){

    int a[]={8,5,78,90,2,45,67};
    int size=sizeof(a)/4;
    int b[size];
    int count=1;
    while(count<=size){
        for(int i=0;i<size;i++){
            if(a[count]<b[i]){
                int c[count];
                int k=i;
                for(int j=0;j<count;j++){
                    c[j]=b[k];
                    k++;
                }
                b[i]=a[count];
                k=0;
                for(int j=i+1;j<=count;j++){
                    b[j]=c[k];
                    k++;
                }
            }
            if(a[count]>=b[i]){
              int c[count-i];
              int k=i+1;

              for(int j=0;j<count-i;j++){
                c[j]=b[k];
                k++;
              }
              b[i+1]=a[count];
              k=0;
              for(int j=i+2;j<size;j++){
                b[j]=c[k];
                k++;
              }
            }
        }
        count++;
        printf("%d %d %d %d %d %d %d\n",b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
    }
}