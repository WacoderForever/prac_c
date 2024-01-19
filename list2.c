#include <stdio.h>
#include <stdlib.h>

struct listNode{
    char data;
    struct listNode *nextPtr;
};
typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void insert(ListNodePtr *sPtr,char value);
char delete(ListNodePtr *sPtr,char value);
int IsEmpty(ListNodePtr sPtr);
void printList(ListNodePtr sPtr);
void instructions();

int main(int argc,char **argv){
    ListNodePtr startPtr=NULL;
    instructions();
    int choice;
    printf("Enter choice:");
    scanf("%d",&choice);
    char value;
    while(choice !=3){
        switch(choice){
            case 1:
                printf("Enter value to insert:");
                scanf("%s",&value);
                insert(&startPtr,value);
                printList(startPtr);
                break;
            case 2:
                if(!IsEmpty(startPtr)){
                    printf("Enter value to delete:");
                    scanf("%s",&value);
                    if(delete(&startPtr,value)){
                        printf("%c is deleted\n",value);
                        printList(startPtr);
                        break;
                    }
                }
                else{
                    puts("The list is empty");
                    break;
                }
            default:
                puts("Invalid choice");
                instructions();
                break;
        
    }
    printf("Enter choice:");
    scanf("%d",&choice);
    }
    puts("End of run");
    return 0;
}
void instructions(){
    puts("Enter 1 to insert a node.");
    puts("Enter 2 to delete a node.");
    puts("Enter 3 to end.");
}
void insert(ListNodePtr *sPtr,char value){
    ListNodePtr newPtr=malloc(sizeof(ListNode));
    if(newPtr !=NULL){
    newPtr->data=value;
    newPtr->nextPtr=NULL;

    ListNodePtr previousPtr=NULL;
    ListNodePtr currentPtr=*sPtr;
    while((currentPtr !=NULL)&&(value>currentPtr->data)){
        previousPtr=currentPtr;
        currentPtr=currentPtr->nextPtr;
    }
    //insert in first position
    if(previousPtr==NULL){
        newPtr->nextPtr=*sPtr;
        *sPtr=newPtr;
    }
    //insert betwen prev and current
    else{
        previousPtr->nextPtr=newPtr;
        newPtr->nextPtr=currentPtr;
    }
    }
    else{
        printf("No memory to insert node");
    }
}
void printList(ListNodePtr sPtr){
    if(!IsEmpty(sPtr)){
        while(sPtr !=NULL){
            printf("%c---->",sPtr->data);
            sPtr=sPtr->nextPtr;
        }
    }
    else{
        puts("The list is empty");
    }
    printf("NULL\n");
}
int IsEmpty(ListNodePtr sPtr){
    return sPtr==NULL;
}
char delete(ListNodePtr *sPtr,char value){
    if(value==(*sPtr)->data){
        ListNodePtr tempPtr=*sPtr;
        *sPtr=(*sPtr)->nextPtr;
        free(tempPtr);
        return value;
    }
    else{
       ListNodePtr currentPtr=(*sPtr)->nextPtr;
       ListNodePtr previousPtr=*sPtr;

       while((currentPtr !=NULL)&&(value != currentPtr->data)){
        previousPtr=currentPtr;
        currentPtr=currentPtr->nextPtr;
       }
       if(currentPtr!=NULL){
            ListNodePtr tempPtr=currentPtr;
            previousPtr->nextPtr=currentPtr->nextPtr;
            free(tempPtr);
            return value;
       }
    }
    return '\0';
}