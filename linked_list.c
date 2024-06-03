#include <stdio.h>
#include <stdlib.h>
struct listnode{
    char data;
    struct listnode *nextPtr;
};
typedef struct listnode ListNode; //synonym for struct listnode
typedef ListNode *ListNodePtr;    //synonym for ListNode*
//function prototypes
void insert(ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(int argc,char **argv){
    ListNodePtr startptr=NULL;
    char value;
    int choice;
    instructions();
    printf("Enter your choice:");
    scanf("%d",&choice);
    while(choice!=3){
        switch(choice){
            case 1:
                    printf("Enter character to insert in the list:");
                    scanf("%s",&value);
                    insert(&startptr,value);
                    printList(startptr);
                break;
            case 2:
                    printf("Enter character to delete:");
                    scanf("%s",&value);
                    if(!isEmpty(startptr)){
                        if(delete(&startptr,value)){
                            printf("%c is deleted\n",value);
                            printList(startptr);
                        }
                        else{
                            printf("%c is not in the list\n",value);
                        }
                    }
                    else{
                        puts("The list is empty");
                    }
                break;
            default:
                    printf("Invalid entry.");
                    instructions();
                    break;
        }
        printf("Enter choice:");
        scanf("%d",&choice);
    }
    puts("End of run");
}
void instructions(){
    puts("Enter the following commands:");
    printf("1.Insert item into list:\n");
    printf("2.Delete item in list:\n");
    puts("3.To end.");
}
void insert(ListNodePtr *sPtr,char value){
    ListNodePtr newPtr=malloc(sizeof(ListNode));
    if(newPtr != NULL){
        //new node
        newPtr->data=value;
        newPtr->nextPtr=NULL;

        ListNodePtr currentPtr=*sPtr;
        ListNodePtr previousPtr=NULL;
        while((currentPtr !=NULL)&&(value>currentPtr->data)){
            previousPtr=currentPtr;
            currentPtr= currentPtr->nextPtr;
        }
        //insert node at first position
        if(previousPtr==NULL){
            newPtr->nextPtr=*sPtr;
            *sPtr=newPtr;
        }
        //insert node between previous node and current node
        else{
            previousPtr->nextPtr=newPtr;
            newPtr->nextPtr=currentPtr;
        }
    }
    else{
        printf("No memory space left to create new node\n");
    }

}
void printList(ListNodePtr currentPtr){
    if(isEmpty(currentPtr)){
        printf("The list is empty\n");
    }
    else{
        puts("The list is:");
        while(currentPtr!=NULL){
            printf("%c--->",currentPtr->data);
            currentPtr=currentPtr->nextPtr;
        }
        printf("NULL\n");
    }
}
// return 1 if list is empty or zero otherwise 
int isEmpty(ListNodePtr sPtr){
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
        ListNodePtr previousPtr=*sPtr;
        ListNodePtr currentPtr=(*sPtr)->nextPtr;

        while((currentPtr != NULL)&&(currentPtr->data != value)){
            previousPtr=currentPtr;
            currentPtr=currentPtr->nextPtr;
        }
        if(currentPtr != NULL){
            ListNodePtr tempPtr=currentPtr;
            previousPtr->nextPtr=currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }
    return '\0';
}