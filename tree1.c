#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node *leftNode;
    int value;
    struct Node *rightNode;
};

struct Node * createNode(){
    struct Node *newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode=NULL;
    return newNode;
}

void addNode(struct Node **head,int value){
    if((*head)==NULL){
        (*head)->value=value;
        (*head)->leftNode=NULL;
        (*head)->rightNode=NULL;
        return;
    }
    if((value%20)==0){
        while((*head)->leftNode != NULL){
            *head=(*head)->rightNode;
        }
        (*head)->leftNode->value=value;
        (*head)->leftNode->leftNode=NULL;
        (*head)->leftNode->rightNode=NULL;
        return;
    }
    if((value%20)!=0){
        while((*head)->rightNode != NULL){
            *head=(*head)->rightNode;
        }
        (*head)->rightNode->value=value;
        (*head)->rightNode->rightNode=NULL;
        (*head)->rightNode->leftNode=NULL;
        return;
    }
}

void printTree(struct Node *head){
    if(head==NULL){
        printf("Empty tree\n");
        return;
    }
    while(head!=NULL){
        printf("Value: %d",head->value);
        printf("ValueL: %d",head->leftNode->value);
        printf("ValueR: %d\n",head->rightNode->value);
        head=head->rightNode;
    }
}

int main(){
    struct Node *newNode=createNode();
    addNode(&newNode,10);
    addNode(&newNode,20);
    addNode(&newNode,30);
    addNode(&newNode,40);
    addNode(&newNode,50);
    printTree(newNode);
}