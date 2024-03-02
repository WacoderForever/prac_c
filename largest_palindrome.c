#include "allheaders.h"


int find_number_of_digits(int num){

    int div=100000;
    int temp_num=num;
    int count=0;

    while(div > 1){

        if((int)temp_num/div>=1){

            ++count;
            div/=10;
            break;
        }

        div/=10;

    }

    while(div>=1){

        div/=10;
        ++count;
    }

    return count;
}

int reversed_number(int num){

    int dig=find_number_of_digits(num);
    int temp_num=num;
    int num2=0;
    int count=1;
       
    while(dig > 1){

        int dig2=dig-1;

        while(dig2>0){

            int k=(int)pow(10,dig2);
            temp_num=temp_num%k;
            --dig2;

        }

        num2+=(int)temp_num*pow(10,dig-1);
        temp_num=(int)num/pow(10,count);
        ++count;
        dig--;
    }

    num2+=temp_num;

    return num2;
}

int palindrome(int num){

    int num2=reversed_number(num);
    
    if((num-num2)==0){

        return 1;
    }

    else{

        return 0;
    }
}


int main(){

    long int max=0;
    int first=100;
    long int product;

    while(first<1000){

        int second=100;

        while(second<1000){

            product=first*second;

            if(palindrome(product)==1){

                if(max <= product){

                    max=product;
                }
            }

            second++;
        }

        first++;
    }

    printf("The max palindrome product is: %ld\n",max);

    return 0;

}