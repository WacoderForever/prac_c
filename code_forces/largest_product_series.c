#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(){
    FILE *input;
    long max_product = 1;
    long temp_max = 1;
    char ch;
    input = fopen("1000_digit.txt","r");
    while(!feof(input)){
        ch = fgetc(input);
        int num;
        for(int i=0;i<13;i++){
            if(!isdigit(ch)){
                ch = fgetc(input);
                i--;
            }
            else{
                num = ch - '0';
                if(num == 0){
                    temp_max = 1;
                    ch = fgetc(input);
                    break;
                }
                temp_max *= num;
            }
        }
        if(temp_max > max_product) max_product = temp_max;
        temp_max = 1;
    }
    printf("Max: %ld\n",max_product);

    return 0;
}