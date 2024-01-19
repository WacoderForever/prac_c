#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dice(){
    int k;
    k=1+rand()%6;
    return k;
}

int main(){
    srand(time(NULL));
    int count=0;
    int headcount=0;
    int tailcount=0;
    while(count<100){
        if(dice()%2==0){
            printf("H\n");
            ++headcount;
            ++count;
        }
        else{
            printf("T\n");
            ++tailcount;
            ++count;
        }

    }
    printf("Probability of head:%d%c\n",headcount,'%');
    printf("Probability of tail:%d%c\n",tailcount,'%');



}