#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int prime_count = 0;

bool is_prime(long n){
    if(n==2) return true;
    if(n%2 == 0) return false;
    int div = 3;
    int count = 1;
    while(div <= n){
        if(n%div == 0) ++count;
        div += 2;
        if(count>2) return false;
    }
    return true;
}

long nth_prime(){
    int count = 2;
    long n = 5;
    while(true){
        if(is_prime(n)) ++count;
        if(count == 10001) return n;
        n += 2;
    }
}

int main(){
    printf("%ld is the 10001st prime\n",nth_prime());
    return 0;
}