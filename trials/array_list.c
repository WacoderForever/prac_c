#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int arr[100];
    int size;
}List;

void initList(List *list){
    list->size=0;
}

void insert(List *list,int value){
    if(list->size<100){
        list->arr[size]=value;
        ++list->size;
    }
    else{
        printf("List is full.\n");
    }
}

void delete(List *list,int value){
    int i;
    for(i=0;i<=list->size;i++){
        if(value==list->arr[i]){
            for(int j=i;j<list->size-1;j++){
                list->data[j]=list->data[j+1];
            }
            list->size--;
            return;
        }
    }
}