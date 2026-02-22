#include <stdio.h>

int main(){
    int Ar[] = {1,3,5,7,8};
    int n = 5;
    int j = n;
    int k = 3;
    int item = 100;
    printf("Initial Array:\n");
    for(int i=0;i<n;i++){
        printf("[%d] : %d\n",i,Ar[i]);
    }
    n++;
    while(j >= k){
        Ar[j] = Ar[j-1];
        j--;
    }
    Ar[k] = item;

    printf("Final Array:\n");
    for(int i=0;i<n;i++){
        printf("[%d] : %d\n",i,Ar[i]);
    }
    return 0;
}