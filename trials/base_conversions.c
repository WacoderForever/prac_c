#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *hex(int dec){
    char *res;
    char *k[17]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int rem;
    while(dec>0){
        rem=dec%16;
        dec=dec/16;
        strcat(res,k[rem]);
    }
    return res;

}

int main(){
    int dec;
    printf("Enter the decimal number:");
    scanf("%d",&dec);
    printf("Hex equivalent:%s",hex(dec));

}