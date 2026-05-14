#include <stdio.h>

long pthfactor(long n,long p){
    long count = 0;
    
    for(long div = 1; div <= (n/2); div++){
        if(n % div == 0){
            count++;
            if(count == p){
                return div;
            }
        }
    }
    if((count+1)==p) return n;
    else{
        return -1;
    }
     
}

int main(){
    printf("12th factor is: %ld\n",pthfactor(12,6));
}