#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define bool int

bool isEven(unsigned long long value ){
    return (value%2 == 0);
}

bool isPrime(unsigned long long num){
    if(num==1) return FALSE;
    int count=2;
    unsigned long long  div = (unsigned long long )num/2;
    for(unsigned long long i=div;i>1;i--){
        if((num%i)==0){
            count++;
            break;
        }
    }
    if(count>2) return FALSE;
    return TRUE;
}

bool GoldBach(unsigned long long num){
    unsigned long long  k=0;
    for(unsigned long long  i=num-1;i>1;i--){
        if(isPrime(i)){
            k=num-i;
            if(isPrime(k)){
                printf("%lld + %lld = %lld \n",i,k,num);
                return TRUE;
            }
        }
    }
    return FALSE;
}

int main(){
    for(unsigned long long i=3;i>2;i++){
        if(isEven(i)){
            bool z=GoldBach(i);
            if(!z){
                printf("Goldbach Error: %lld\n",i);
                break;
            }
        }
    }
    return 0;
}