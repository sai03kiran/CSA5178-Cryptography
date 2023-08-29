#include <stdio.h>
#include <string.h>

// Size of the matrix (Hill cipher is typically 2x2 or 3x3)
#define MATRIX_SIZE 3

// Function to encrypt a message using Hill cipher
void encrypt(char message[], int key[][MATRIX_SIZE]) {
    int messageLength = strlen(message);
    int encryptedMessage[messageLength];
    
    for (int i = 0; i < messageLength; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            encryptedMessage[i + j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                encryptedMessage[i + j] += (key[j][k] * (message[i + k] - 'A'));
            }
            encryptedMessage[i + j] %= 26;
        }
    }
    
    printf("Encrypted Message: ");
    for (int i = 0; i < messageLength; i++) {
        printf("%c", encryptedMessage[i] + 'A');
    }
    printf("\n");
}

int main() {
    // Define the encryption key matrix (3x3 matrix example)
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };
    
    char message[100];
    printf("Enter the message to encrypt (in uppercase): ");
    scanf("%s", message);
    
    encrypt(message, key);
    
    return 0;
}
