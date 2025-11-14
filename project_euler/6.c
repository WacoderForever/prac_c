#include <stdio.h>

long S(int n){
    return (n*(n+1))/2;
}

long squareOfSum(int n){
    long r=S(n);
    return r*r;
}

long sumOfSquares(int n){
  return (n*(n+1)*(2*n+1))/6;
}

int main(){
    long sq_r = squareOfSum(100);
    printf("squareOfSum: %ld\n",sq_r);
    long Ssq_r = sumOfSquares(100);
    printf("sumOfSquares: %ld\n",Ssq_r);
    long diff = sq_r - Ssq_r;
    printf("%ld\n",diff);
    return 0;
}