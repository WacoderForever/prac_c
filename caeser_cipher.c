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
    printf("The text is: %s\n", text);
    printf("The cipher form is: %s\n", cipher);


    // free text and cipher
    free(text);
    free(cipher);
    return 0;
}
