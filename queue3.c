#include <stdio.h>
#include <stdlib.h>

struct queueNode{
    char data;
    struct queueNode *nextnode;
};
typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

void enqueue(QueueNodePtr *beginPtr,QueueNodePtr *lastPtr,char value);
char dequeue(QueueNodePtr *sPtr);
int IsEmpty(QueueNodePtr sPtr);
void printQueue(QueueNodePtr sPtr);
void instructions();
int main(){
    QueueNodePtr beginQueue=NULL;
    QueueNodePtr lastQueue=NULL;
    int choice;
    char value;
    instructions();
    printf("Enter choice:");
    scanf("%d",&choice);
    while(choice !=3){
        switch(choice){
            case 1:
                printf("Enter value to enqueue:");
                scanf("%s",&value);
                enqueue(&beginQueue,&lastQueue,value);
                printQueue(beginQueue);
                break;
            case 2:
                if(!IsEmpty(beginQueue)){
                    printf("Value dequeued is %c\n",dequeue(&beginQueue));
                    printQueue(beginQueue);
                }
                else{
                    printf("Queue is empty");
                }
                break;
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
    puts("Enter 1 to enqueue.");
    puts("Enter 2 to dequeue.");
    puts("Enter 3 to end.");
}
void enqueue(QueueNodePtr *beginPtr,QueueNodePtr *lastPtr,char value){
    QueueNodePtr newnode=malloc(sizeof(QueueNode));
    if(newnode !=NULL){
        newnode->data=value;
        newnode->nextnode=NULL;
        if(IsEmpty(*beginPtr)){
            *beginPtr=newnode;
        }
        else{
            (*lastPtr)->nextnode=newnode;
        }
        *lastPtr=newnode;
        
    }
    else{
        puts("No free memory to allocate for new queue node.");
    }
}
void printQueue(QueueNodePtr sPtr){
    if(!IsEmpty(sPtr)){
        while(sPtr !=NULL){
            printf("%c ",sPtr->data);
            sPtr=sPtr->nextnode;
        }
    }
    else{
        puts("Queue is empty.");
    }
    puts("NULL");

}
int IsEmpty(QueueNodePtr sPtr){
    return sPtr==NULL;
}
char dequeue(QueueNodePtr *sPtr){
    QueueNodePtr tempPtr=*sPtr;
    char r=tempPtr->data;
    *sPtr=(*sPtr)->nextnode;
    free(tempPtr);
    return r;

}

