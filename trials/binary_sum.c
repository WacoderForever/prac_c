#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int n;
    printf("Enter n:");
    scanf("%d",&n);
    unsigned long ans=0;
    for(int i=n-1;i>=0;i--){
        ans+=(unsigned long)pow(2,i);
    }
    printf("%lu\n",ans);
    return 0;
}