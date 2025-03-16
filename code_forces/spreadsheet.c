#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *to_alph(char *rc){
    int i=1; //skip R
    int row=0;
    int col=0;
    while(isdigit(rc[i])){
        row=10*row + (rc[i]-'0');
        i++;
    }
    i++; //skip C
    while(isdigit(rc[i])){
        col=10*col +(rc[i]-'0');
        i++;
    }
    int div=col/26;
    int rem=col%26;
    char *alph_col;
    if(rem==0){
        div--;
        while(div > 0){
            div--;
            char c='A'+div;
            strcat(alph_col,c);
        }
        char c='Z';
        strcat(alph_col,c);
    }
    else{
        while(div > 0){
            div--;
            char c='A'+div;
            srtcat(alph_col,c);
        }
        char c='A'-1+rem;
        strcat(alph_col,);
    }
}

int main(){
    unsigned long long n;
    printf("Enter n:");
    scanf("%lld",&n);
    if((n<1) || (n>100000)){
        printf("n out of range.\n");
        return 1;
    }
    char *coordinates[n];
    int i=0;
    while(i<n){
        scanf("%s",coordinates[i]);
        i++;
    }
}