#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int data;
    struct Node* next;
}Node;

Node* createNode(int data){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->data=value;
    newNode->next=NULL;
    return newNode;
}

void insertAtBegin(Node **head,int value){
    Node* newNode=createNode(value);
    newNode->next=*head;
    *head=newNode;
}