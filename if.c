#include <stdio.h>


int main(){
    FILE *even,*odd;
    int number=0;
    even=fopen("even.txt","w");
    odd=fopen("odd.txt","w");

    for(int k=1;k<100;k++){
        k%2==0 ? fprintf(even,"\t %5d",k) : fprintf(odd,"\t %5d",k);
    }

    fclose(even);
    fclose(odd);

    return 0;
}