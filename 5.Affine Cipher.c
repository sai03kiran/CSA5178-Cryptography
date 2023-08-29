#include <stdio.h>
#include <ctype.h>

// Function to perform Affine encryption
void affineEncrypt(char *plaintext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int x = plaintext[i] - base;
            plaintext[i] = (a * x + b) % 26 + base;
        }
    }
}

// Function to perform Affine decryption
void affineDecrypt(char *ciphertext, int a, int b) {
    // Calculate the modular multiplicative inverse of 'a' (assuming m = 26)
    int aInverse = -1;
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            aInverse = i;
            break;
        }
    }

    if (aInverse == -1) {
        printf("Multiplicative inverse of 'a' does not exist.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int x = ciphertext[i] - base;
            // Apply modular inverse to decrypt
            ciphertext[i] = (aInverse * (x - b + 26)) % 26 + base;
        }
    }
}

int main() {
    char plaintext[] = "Hello, World!";
    int a = 5;
    int b = 8;

    printf("Original: %s\n", plaintext);

    affineEncrypt(plaintext, a, b);
    printf("Encrypted: %s\n", plaintext);

    affineDecrypt(plaintext, a, b);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}

