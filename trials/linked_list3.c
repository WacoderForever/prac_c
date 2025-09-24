#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int data;
    struct List *next;
}List;

void insert(List **head,int value){
    List *new = (List*)malloc(sizeof(List));
    if(new==NULL) return;

    new->data=value;
    new->next=NULL;

    //case 1: at the first index
    while((*head == NULL) || ((*head)->data < value)){
        new->next=*head;
        *head=new;
        return;
    }

    //case 2: traverse to find position
    List *curr=*head;
    while((curr->next != NULL) && (curr->next->data < value)){
        curr=curr->next;
    }
    new->next=curr->next;
    curr->next=new;
}

void traverse(List *head){
    List *temp = head;
    while(temp != NULL){
        printf("%d\n",temp->data);
        temp=temp->next;
    }
    free(temp);
}

void delete(List **head, int value){
    if(*head == NULL) return;

    List *temp=*head;
    //case 1: delete head
    if((*head)->data == value){
        *head = (*head)->next;
        free(temp);
        return;
    }
    //case 2: search inside list
    List *prev=NULL;
    while((temp != NULL) && (temp->data != value)){
        prev=temp;
        temp=temp->next;
    }

    if(temp==NULL){
        printf("%d not found\n",value);
        return;
    }
    prev->next = temp->next;
    free(temp);
    return;
}

int main(){
    List *head = NULL;

    insert(&head, 24);
    insert(&head, 5);
    insert(&head, 2);
    insert(&head, 8);
    insert(&head, 3);    

    printf("List contents:\n");
    traverse(head);

    printf("Deleting 3...\n");
    delete(&head, 3);
    traverse(head);

    return 0;
}