#include "allheaders.h"

int binop(int a,int b,int *c){
    int ans=(a^b)^(*c);
    int k=((a^b)*(*c));
    (k==1)?((*c)=k):((*c)=(a*b));
    return ans;
}
void add_bit(int A[],int B[],int C[],int n){
    int carry=0;
    for(int i=n-1;i>0;i--){
        C[i+1]+=binop(A[i],B[i],&carry);
    }
    C[0]=carry;
}

void printarray(int A[],int n){
    for(int i=0;i<n;i++){
        printf("%d, ",A[i]);
    }
    puts(" ");
}

int main(){
    int A[]={1,0,1,0,1,1};
    int B[]={0,1,1,1,0,1};
    int C[7]={0};
    add_bit(A,B,C,6);
    printarray(C,7);
}