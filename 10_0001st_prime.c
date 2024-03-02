#include "allheaders.h"

int prime(int num){

    int count=0,div=1;

    while(div<num){

        if((num%div)==0){

            ++count;
        }

        ++div;
    }

    if(count==1){

        return 1;
    }

    else{

        return 0;
    }
}

int main(){

    int prime_count=1;
    long int the_prime;
    int num=3;

    while(prime_count<=10001){

        if((prime(num))==1){

            prime_count++;
        }

        if(prime_count==10001){

            the_prime=num;
            break;
        }

        num+=2;

    }

    printf("The 10001st prime is %ld\n",the_prime);

    return 0;
}