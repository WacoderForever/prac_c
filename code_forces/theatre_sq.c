#include <stdio.h>
#include <stdlib.h>

unsigned long long Myceil(double in){
    unsigned long long k=(unsigned long long)in;
    if((in-k) > 0){
        return k+1;
    }
    return k;
}

int main(){
    unsigned long long n,m,a;
    unsigned long long num;
     scanf("%lld %lld %lld", &n, &m, &a);
    if((n<1)||(n>1000000000)){
        printf("n out of range");
        return 1;
    }
    if((m<1)||(m>1000000000)){
        printf("m out of range");
        return 1;
    }
    if((a<1)||(a>1000000000)){
        printf("a out of range");
        return 1;
    }

    num+=Myceil((double)n/(double)a)*Myceil((double)m/(double)a);
    printf("%lld\n",num);

    return 0;
}