#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#pragma pack(1)
int isprime(int d){
    int count=0;
    int div=1;
    while(div<=d){
        if(d%div==0){
            ++count;
        }
        ++div;
    }
    if(count==2){
        return 1;
    }
    else{
        return 0;
    }
}
void main(){
    long k;
    printf("Enter integer:");
    scanf("%l",&k);
    int ans[k];
    puts("");
    int count=0;
    int factor=2;
        while(k>1){
            if((isprime(factor)==1)&&(k%factor==0)){
                ans[count]=factor;
                ++count;
                k=k/factor;
            }
            else{
                ++factor;
            }
        }
        ans[count]=1;
        printf("The prime factors are:");
        for(int i=0;(i<=count);++i){
            printf("%d",ans[i]);
            if(i!=count){
                printf(" x ");
            }
        }

}