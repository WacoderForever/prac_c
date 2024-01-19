#include <stdio.h>
#include <stdlib.h>
int merge(int left[],int right[]){
    int l_size=sizeof(&left);
    int r_size=sizeof(&right);
    int full=l_size+r_size;
    int final[full];
    int left_index=0;
    int right_index=0;
    int count=0;
    while(count<full){
        if(left[left_index]<right[right_index]){
            final[count]=left[left_index];
            left_index++;
            count++;
        }
        else{
            final[count]=right[right_index];
            right_index++;
            count++;
        }
    }
    return final;
}
int split(int a[],int size){
    if(size==1){
        return a[size-1];
    }
    int mid=size/2;
    int left[mid];
    int k=size-mid;
    int right[k];
    return merge(split(left,mid),split(right,k));
}


int main(){
    int yt[]={1,2,5,1,9,44,34};
    int size=sizeof(yt)/sizeof(int);
    split(yt,size);
}