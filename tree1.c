#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node *leftNode;
    int value;
    struct Node *rightNode;
};

struct Node * createNode(int value){
    struct Node *newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->value=value;
    newNode->leftNode=NULL;
    newNode->rightNode=NULL;
    return newNode;
}

void adddNode(struct Node **head,int value){
    if((*head)==NULL){
        (*head)=createNode(value);
        return;
    }
    struct Node *temp=(*head);

    if((value%20)==0){
        while(temp->leftNode != NULL){
            temp=temp->rightNode;
        }
        temp->leftNode=createNode(value);
        return;
    }
    while(temp->rightNode != NULL){
        temp=temp->rightNode;
    }
    temp->rightNode=createNode(value);
    return;
}

void printTree(struct Node *head){
    struct Node *temp=head;
    //printing using inorder trasversal
    while(temp !=NULL){
        printf("valueL: %d\n",temp->leftNode->value);
        printf("valueM: %d\n",temp->value);
        printf("valueR: %d\n",temp->rightNode->value);
        printf("\n\n");
        temp=temp->rightNode;
    }
}

int main(){
    struct Node *tree=NULL;
    for(int i=10;i<80;i+=10){
        adddNode(&tree,i);
    }
    printTree(tree);
}