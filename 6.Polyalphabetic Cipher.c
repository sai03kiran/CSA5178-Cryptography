#include <stdio.h>
#include <string.h>
#include <ctype.h>
void vigenereEncrypt(char *plaintext, char *key) {
    int plaintextLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (int i = 0; i < plaintextLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int keyIndex = i % keyLen;
            int shift = tolower(key[keyIndex]) - 'a';
            plaintext[i] = (plaintext[i] - base + shift) % 26 + base;
        }
    }
}
void vigenereDecrypt(char *ciphertext, char *key) {
    int ciphertextLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (int i = 0; i < ciphertextLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int keyIndex = i % keyLen;
            int shift = tolower(key[keyIndex]) - 'a';
            ciphertext[i] = (ciphertext[i] - base - shift + 26) % 26 + base;
        }
    }
}

int main() {
    char plaintext[] = "Hello, World!";
    char key[] = "KEY";

    printf("Original: %s\n", plaintext);

    vigenereEncrypt(plaintext, key);
    printf("Encrypted: %s\n", plaintext);

    vigenereDecrypt(plaintext, key);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}

