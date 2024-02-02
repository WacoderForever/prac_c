#include "allheaders.h"

char *encode(char *plaintext, char *key) {

    char *ciphertext = (char*)malloc(strlen(plaintext) + 1);

    if (ciphertext == NULL) {

        perror("Failed to allocate memory for ciphertext");
        exit(1);
    }

    int keyLength = strlen(key);
    int keyIndex = 0; // Use keyIndex to cycle through key characters

    for (int i = 0; plaintext[i] != '\0'; i++) {

        if (isalpha(plaintext[i])) { // Check if the character is alphabetic
            char base = islower(plaintext[i]) ? 'a' : 'A';
            char keyBase = islower(key[keyIndex]) ? 'a' : 'A';
            // Adjust for upper/lower case in plaintext and key
            ciphertext[i] = base + (tolower(plaintext[i]) - base + tolower(key[keyIndex]) - keyBase) % 26;
            keyIndex = (keyIndex + 1) % keyLength; // Move to the next key character

        } 
        else {
            // Non-alphabetic characters are copied as is
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
    return ciphertext;
}

char *decode(char *ciphertext, char *key) {

    char *plaintext = (char*)malloc(strlen(ciphertext) + 1);

    if (plaintext == NULL) {
        perror("Failed to allocate memory for plaintext");
        exit(1);
    }

    int keyLength = strlen(key);
    int keyIndex = 0; // Use keyIndex to cycle through key characters

    for (int i = 0; ciphertext[i] != '\0'; i++) {

        if (isalpha(ciphertext[i])) { // Check if the character is alphabetic
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            char keyBase = islower(key[keyIndex]) ? 'a' : 'A';
            // Adjust for upper/lower case in ciphertext and key, and perform the reverse operation
            int shift = tolower(key[keyIndex]) - keyBase;
            int originalPosition = tolower(ciphertext[i]) - base - shift;
            if (originalPosition < 0) originalPosition += 26; // Ensure the position is not negative
            plaintext[i] = base + originalPosition % 26;
            keyIndex = (keyIndex + 1) % keyLength; // Move to the next key character
        } 
        
        else {
            // Non-alphabetic characters are copied as they are
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
    return plaintext;
}


int main() {

    char *text = NULL;
    size_t size = 0;
    printf("Enter text: ");
    getline(&text, &size, stdin); // Use getline for simplicity
    text[strcspn(text, "\n")] = 0; // Remove newline character

    char *key = NULL;
    size = 0;
    printf("Enter key: ");
    getline(&key, &size, stdin);
    key[strcspn(key, "\n")] = 0; 

    char *cipher = encode(text, key);
    char *plain= decode(cipher,key);
    printf("Entered text: %s\n", text);
    printf("Entered key: %s\n", key);
    printf("Encoded text: %s\n", cipher);
    printf("Decoded text: %s\n", plain);

    
    // Free the allocated memory
    free(text);
    free(key);
    free(cipher);
    free(plain);

    return 0;
}
