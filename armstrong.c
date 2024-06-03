#include "allheaders.h"

int main(){

    int number=0;

    while(number != -1){

        char *num_str=NULL;
        size_t size =0;
        printf("Enter number (enter negative number to quit):");
        getline(&num_str,&size,stdin);
        num_str[strcspn(num_str,"\n")]=0;

        int num_of_digits=strlen(num_str);
        number=atoi(num_str);
        if(number < 0){
            break;
        }
        int temp=number;

        int div_pow=num_of_digits-1;
        int value=0;
        int total=0;
        //iterate over the digits

        for(int i=0;i<num_of_digits;i++){

            value=temp/pow(10,div_pow);
            temp-=(value*(pow(10,div_pow)));
            total+=pow(value,num_of_digits);
            div_pow--;
        }

        if(total==number){

            printf("%i is an armstrong number\n",number);
            
        }
        else{

        printf("%i is not an armstrong number\n",number);

        }

    }

    return 0;
}