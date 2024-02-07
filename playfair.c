#include "allheaders.h"
#define MATRIX_ROW 5
#define MATRIX_COLUMN 5

void create_matrix(char *plaintext){
    
}


char *encode(char *plaintext,char *key){
    char *ciphertext=(char*) malloc(strlen(plaintext)+1);
    
    if(ciphertext==NULL){
        perror("Memory not allocated for ciphertext");
        exit(1);
    }

}

int main(){

    char *text=NULL;
    size_t size=0;
    printf("Enter text: ");
    getline(&text,&size,stdin);
    text[(strcspn(text,"\n"))]=0; //removing new line character in the string

    char *key=NULL;
    size=0;
    printf("Enter key: ");
    getline(&key,&size,stdin);
    key[(strcspn(text,"\n"))]=0;

    printf("The entered text is: %s\n",text);
    printf("The entered key is: %s\n",key);


    return 0;
}