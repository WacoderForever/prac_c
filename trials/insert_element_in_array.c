#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void print_arr_vals(int *arr,size_t len){
    puts("Current values of the array: ");
    for(int i=0;i<len;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}


int main(){
    int p[MAX] = {10,20,30,40,50};
    int len = 5;
    print_arr_vals(p,len);
    int pos;
    int new_num;
    printf("\nEnter position you want to insert the number in the array (first position is 1):");
    scanf("%d",&pos);
    printf("\nEnter the number you wish to insert in the array:");
    scanf("%d",&new_num);
    //move the rightmost values
    for(int j=len;j<=pos;j--){
        p[j] = p[j-1];
    }
    ++len;
    //insert the value
    p[pos-1] = new_num;
    print_arr_vals(p,len);

    return 0;
}