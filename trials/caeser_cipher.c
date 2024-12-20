#include "allheaders.h"

char *encode(char *plaintext, int key) {
    int i = 0;
    char *ciphertext = (char *)malloc(strlen(plaintext) + 1); // +1 for the null terminator

    if (ciphertext == NULL) {
        perror("Failed to allocate memory for ciphertext");
        exit(1);
    }

    while (plaintext[i] != '\0') {
        char ch = tolower(plaintext[i]); // Convert to lowercase

        if (ch >= 'a' && ch <= 'z') {
            // Perform the Caesar cipher shift
            int shiftedPosition = ((ch - 'a') + key) % 26;
            ciphertext[i] = 'a' + shiftedPosition;
        } else {
            // Copy the character as is (e.g., space, punctuation)
            ciphertext[i] = plaintext[i];
        }

        i++;
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext

    return ciphertext;
}


char *decode(char *ciphertext,int key){
    int i=0;
    char *plaintext=(char*)malloc(strlen(ciphertext)+1); //includeing the null terminator

    if(plaintext==NULL){
        perror("Failed to allocate memory for plaintext");
        exit(1);
    }

    while(ciphertext[i] != '\0'){
        char c=tolower(ciphertext[i]);

        if(c >= 'a' && c<='z'){

            int shiftedPosition=((c-'a')-key)%26;
            if(shiftedPosition<0){
                plaintext[i]='z'+shiftedPosition+1;
            }
            else{
            plaintext[i]='a'+shiftedPosition;
            }

        }
        else{

            plaintext[i]=ciphertext[i];

        }
        i++;

    }

    plaintext[i]='\0';

    return plaintext;
}

int main() {
    char *text;
    int size = 1; 
    text = (char *)calloc(size, sizeof(char));

    if (text == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Enter text: ");
    char temp;
    while (scanf("%c", &temp) && temp != '\n') {
        text[size - 1] = temp;
        size++;
        char *new_text = (char *)realloc(text, size * sizeof(char));
        if (new_text == NULL) {
            free(text);
            perror("Failed to reallocate memory");
            return 1;
        }
        text = new_text;
    }

    text[size - 1] = '\0';

    int key;
    printf("Enter key: ");
    scanf("%d", &key);

    char *cipher = encode(text, key);
    char *plain=decode(cipher,key);

    printf("The text is: %s\n", text);
    printf("The cipher form is: %s\n", cipher);
    printf("The plain text is : %s\n",plain);


    // free text and cipher
    free(text);
    free(cipher);
    free(plain);
    return 0;
}
