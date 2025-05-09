#include <stdio.h>
#include <stdlib.h>

int isEven(int num){return (num%2==0) ? 1 : 0;}

typedef struct Node{
    struct Node *next;
    int num;
    struct Node *prev;
}Node;

Node* initNode(int num){
    Node *new=(Node*)malloc(sizeof(Node));
    new->next=NULL;
    new->num=num;
    new->prev=NULL;

    return new;
}

void deleteNode(Node *head, int num){
    Node *temp = head;
    while (temp != NULL && temp->num != num) {
        temp = temp->next;
    }
    //number does not exist
    if (temp == NULL) {
        printf("The number does not exist in the list.\n");
        return;
    }
    // If the node to be deleted is the only node in the list
    if (temp->prev == NULL && temp->next == NULL) {
        free(temp);
        head = NULL;  
        printf("Successfully deleted the node.\n");
        return;
    }
    // If the node to be deleted is the head (first node)
    if (temp->prev == NULL) {
        head = temp->next;  
        head->prev = NULL;  
        free(temp);
        printf("Successfully deleted the node.\n");
        return;
    }

    // If the node to be deleted is the last node
    if (temp->next == NULL) {
        temp->prev->next = NULL;  
        free(temp);
        printf("Successfully deleted the node.\n");
        return;
    }

    // If the node is in the middle of the list
    temp->prev->next = temp->next;  
    temp->next->prev = temp->prev; 

    free(temp);
    printf("Successfully deleted the node.\n");
}

void addNode(Node **head,int num){
    //if list is empty
    if(*head==NULL){
        *head=initNode(num);
        return ;
    }
    Node *temp=*head;
    while(temp->next != NULL){
        temp=temp->next;
    }
    Node *new=initNode(num);
    if(isEven(num)){
        while((!isEven(temp->num))&&(temp != NULL)){
            if(temp->prev==NULL){
                deleteNode(temp,temp->num);
                *head=initNode(num);
                return;
            }
            temp =temp->prev;
            deleteNode(temp->next,temp->next->num);
        }
    }
    temp->next=new;
    new->prev=temp;
}

void printList(Node *head){
    if(head==NULL){
        printf("Empty list.\n");
        return;
    }
    Node *temp=head;
    while(temp != NULL){
        printf("%d->",temp->num);
        temp=temp->next;
    }
    printf("NULL\n");
}

int main(){
    Node *head=initNode(5);
    addNode(&head,7);
    addNode(&head,3);
    printList(head);
    addNode(&head,4);
    addNode(&head,9);
    printList(head);
    addNode(&head,8);
    printList(head);

    return 0;
}