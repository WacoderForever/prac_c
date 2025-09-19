#include <stdio.h>
#include <stdlib.h>

int is_prime(int n){
    if((n==1) || (n==0)) return 0;
    if((n==2) || (n==3)) return 1;
    if(n%2 == 0) return 0;
    for(int i=3;i*i <= n;i+=2){
        if(n%i == 0) return 0;
    }
    return 1;
}

int greatest_pow(int a,int max){
    int product=a;
    int i=1;
    for(i;i<i+1;i++){
        product *= a;
        if(product >= max) break;
    }
    return i;
}

int main(){
    int product=1;
    for(int i=2;i<21;i++){
        if(is_prime(i)){
            int j=greatest_pow(i,20);
            for(int k=0;k<j;k++){
                product *= i;
            }
        }
    }
    printf("The number: %d\n",product);

    return 0;
}