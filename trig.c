#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int pow(int n,int k){
    int ans;
    while(k>0){
        return 
    }
}
int fact(int n){
    if ((n==1)||(n==0)){
        return 1;
    }
    else{
        return n*fact(n-1);
    }
}

double sin(double x){
    double ans=x;
    int count=1;
    while(count <21){
        ans=ans+(pow(-1,count+2)*pow(x,count))/(fact(count+2));
        count=count+2;
    }
    return ans;

}

int main(){
    double deg;
    printf("Enter degrees in radians:");
    scanf("%f",&deg);
        printf("The result is %.2f",sin(deg));
        return 0;
}