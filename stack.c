#include <stdio.h>
#include <stdlib.h>
struct stackNode{
    char data;
    struct stackNode *nextPtr;
};
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void push(StackNodePtr *sPtr,char value);
char pop(StackNodePtr *sPtr);
void printstack(StackNodePtr sPtr);
int IsEmpty(StackNodePtr sPtr);
void instructions();

int main(int argc,char **argv){
    StackNodePtr startPtr=NULL;
    int choice;
    instructions();
    printf("Enter choice:");
    scanf("%d",&choice);
    char value;
    while(choice !=3){
        switch(choice){
            case 1:
                printf("Enter value to add to stack:");
                scanf("%s",&value);
                push(&startPtr,value);
                printstack(startPtr);
                break;
            case 2:
                if(!IsEmpty(startPtr)){
                    printf("The top value of the stack is now:%c\n",pop(&startPtr));
                    printstack(startPtr);
                    break;
                }
                else{
                    puts("The stack is empty.");
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
    puts("End of run.");
    return 0;
}
void instructions(){
    puts("Enter 1 to push.");
    puts("Enter 2 to pop.");
    puts("Enter 3 to end.");
}
void push(StackNodePtr *sPtr,char value){
    StackNodePtr newPtr=malloc(sizeof(StackNode));
    if(newPtr !=NULL){
        newPtr->data=value;
        newPtr->nextPtr=NULL;
        StackNodePtr currentPtr=*sPtr;
        newPtr->nextPtr=currentPtr;
        *sPtr=newPtr;

    }
    else{
        printf("Stack memory is full!Free up some of the stack.");
    }
}
void printstack(StackNodePtr sPtr){
    if(!IsEmpty(sPtr)){
        while(sPtr!=NULL){
            printf("%c--->",sPtr->data);
            sPtr=sPtr->nextPtr;
        }
    printf("NULL\n");

    }
    else{
        puts("The stack is empty");
    }
}
int IsEmpty(StackNodePtr sPtr){
    return sPtr==NULL;
}
char pop(StackNodePtr *sPtr){
    StackNodePtr tempPtr=*sPtr;
    if((*sPtr)->nextPtr !=NULL){
        *sPtr=(*sPtr)->nextPtr;
         free(tempPtr);
        return (*sPtr)->data;

    }
    else{
        free(tempPtr);
        *sPtr=NULL;
        return '\0';
    }
   
    
}