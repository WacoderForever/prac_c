#include "allheaders.h"

void dec_bin(int dec){
    if(dec>0){
        dec_bin((int)dec/2);
        printf("%d ",dec%2);
    }
    return ;
}

int num_of_digits(long num){
    int count=0;
    long temp=num;

    while(temp>=1){
        temp /= 10;
        count++;
    }
    return count;
}
int main(){
    printf("%d\n",num_of_digits(10011111));

    return 0;
}