#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct treenode{
    struct treenode *leftnode;
    int data;
    struct treenode *rightnode;
};
typedef struct treenode TreeNode;
typedef TreeNode *TreeNodePtr;

void insertnode(TreeNodePtr *sPtr,int value);
void inorder(TreeNodePtr sPtr);
void preorder(TreeNodePtr sPtr);
void postorder(TreeNodePtr sPtr);

int main(int argc,char **argv){
    srand(time(NULL));
    TreeNodePtr startnode=NULL;
    for(int i=0;i<10;++i){
        int value=1+rand()%15;
        printf("%3d",value);
        insertnode(&startnode,value);
    }
    puts(" ");
    puts("Inorder trasversal:");
    inorder(startnode);
    puts(" ");
    puts("Preorder trasversal:");
    preorder(startnode);
    puts(" ");
    puts("Postorder trasversal:");
    postorder(startnode);
    puts(" ");
}
void insertnode(TreeNodePtr *sPtr,int value){
    if((*sPtr)==NULL){
        *sPtr=malloc(sizeof(TreeNode));
        if((*sPtr)!=NULL){
            (*sPtr)->data=value;
            (*sPtr)->leftnode=NULL;
            (*sPtr)->rightnode=NULL;
        }
        else{
            puts("Memory error");
        }
    }
    else{
        if(value<((*sPtr)->data)){
            insertnode(&((*sPtr)->leftnode),value);
        }
        else if(value>((*sPtr)->data)){
            insertnode(&((*sPtr)->rightnode),value);
        }
        else{
            printf("dup");
        }
    }
}
void inorder(TreeNodePtr sPtr){
    if(sPtr !=NULL){
        inorder(sPtr->leftnode);
        printf("%3d",sPtr->data);
        inorder(sPtr->rightnode);
    }
}
void preorder(TreeNodePtr sPtr){
    if(sPtr !=NULL){
        printf("%3d",sPtr->data);
        preorder(sPtr->leftnode);
        preorder(sPtr->rightnode);
    }
}
void postorder(TreeNodePtr sPtr){
    if(sPtr!=NULL){
        postorder(sPtr->leftnode);
        postorder(sPtr->rightnode);
        printf("%3d",sPtr->data);
    }
}
