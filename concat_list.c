#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list1{
    char data;
    struct list1 *nextnode;
};
typedef struct list1 List1Node;
typedef List1Node *List1NodePtr;

void menu(void);
void insert(List1NodePtr *sPtr,char value);
void concat(List1NodePtr sPtr,List1NodePtr vPtr);
void printList(List1NodePtr currentnode);
int isEmpty(List1NodePtr sPtr);
int main(){
    List1NodePtr list1=NULL;
    List1NodePtr list2=NULL;
    char let;
    int choice;
    menu();
    printf("Enter your choice:");
    scanf("%d",&choice);
    while(choice !=4){
    switch(choice){
        case 1:
            int li;
            printf("Enter the list you want to add letter:");
            scanf("%d",&li);
            printf("Enter the letter:");
            scanf("%s",&let);
            if(li==1){
                insert(&list1,let);
                break;
            }
            else{
                insert(&list2,let);
                break;
            }
            
        case 2:
            puts("Concatenated string:");
            concat(list1,list2);
            break;
        case 3:
            puts("List 1:");
            printList(list1);
            puts("List 2:");
            printList(list2);
            break;
        default:
            puts("Invalid choice");
            menu();
            break;

        
    }
    printf("Enter Choice:");
    scanf("%d",&choice);

    }
    puts("Exit successful.");
}
void menu(void){
    puts("Enter 1 to add item to list");
    puts("Enter 2 to concatenate the lists");
    puts("Enter 3 to exit.");
}
void insert(List1NodePtr *sPtr,char value){
    List1NodePtr newnode=malloc(sizeof(List1Node));
    if(newnode !=NULL){
    newnode->data=value;
    newnode->nextnode=NULL;
    List1NodePtr currentnode=*sPtr;
    List1NodePtr prevnode=NULL;
    while((currentnode!=NULL)&&(value>currentnode->data)){
        prevnode=currentnode;
        currentnode=currentnode->nextnode;
    }
    if(prevnode==NULL){
        newnode->nextnode=*sPtr;
        *sPtr=newnode;
    }
    else{
        prevnode->nextnode=newnode;
        newnode->nextnode=currentnode;

    }
    }
    else{
        puts("No free memory to allocate item.");
    }
}
void concat(List1NodePtr sPtr,List1NodePtr vPtr){
    int k;
    List1NodePtr prev1=sPtr;
    List1NodePtr prev2=vPtr;
    while((sPtr->nextnode) !=NULL){
        k++;
        sPtr=sPtr->nextnode;
    }
    while((vPtr->nextnode) !=NULL){
        k++;
        vPtr=vPtr->nextnode;
    }
    char f[k];
    int i=0;
    sPtr=prev1;
    vPtr=prev2;
     while((sPtr->nextnode) !=NULL){
        f[i]=sPtr->data;
        sPtr=sPtr->nextnode;
        i++;
    }
    while((vPtr->nextnode) !=NULL){
        f[i]=vPtr->data;
        vPtr=vPtr->nextnode;
        i++;
    }
   int j=0;
   while(j<k){
    printf("%c",f[j]);
    j++;
   }
}
void printList(List1NodePtr currentPtr){
    if(isEmpty(currentPtr)){
        printf("The list is empty\n");
    }
    else{
        puts("The list is:");
        while(currentPtr!=NULL){
            printf("%c--->",currentPtr->data);
            currentPtr=currentPtr->nextnode;
        }
        printf("NULL\n");
    }
}
int isEmpty(List1NodePtr sPtr){
    return sPtr==NULL;
}
