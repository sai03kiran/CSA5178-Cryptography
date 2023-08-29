#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int modularInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return -1;
}

void hillEncrypt(int keyMatrix[3][3], char *message, int messageLength) {
    int cipherMatrix[messageLength][1];
    
    for (int i = 0; i < messageLength; i++) {
        for (int j = 0; j < 1; j++) {
            cipherMatrix[i][j] = 0;
            for (int x = 0; x < 3; x++)
                cipherMatrix[i][j] += keyMatrix[i][x] * (message[j + x] - 'a');
            cipherMatrix[i][j] %= 26;
        }
    }
    
    printf("Encrypted message: ");
    for (int i = 0; i < messageLength; i++)
        printf("%c", cipherMatrix[i][0] + 'a');
    printf("\n");
}

void hillDecrypt(int keyMatrix[3][3], char *cipher, int cipherLength) {
    int inverseKeyMatrix[3][3];
    
    int determinant = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) -
                      keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) +
                      keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    
    int modInverseDet = modularInverse(determinant, 26);
    
    int adjointMatrix[3][3];
    adjointMatrix[0][0] = (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]);
    adjointMatrix[0][1] = -(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]);
    adjointMatrix[0][2] = (keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]);
    adjointMatrix[1][0] = -(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]);
    adjointMatrix[1][1] = (keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]);
    adjointMatrix[1][2] = -(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0]);
    adjointMatrix[2][0] = (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    adjointMatrix[2][1] = -(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]);
    adjointMatrix[2][2] = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]);
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            inverseKeyMatrix[i][j] = (adjointMatrix[i][j] * modInverseDet) % 26;

    for (int i = 0; i < cipherLength; i += 3) {
        int cipherVector[3];
        for (int j = 0; j < 3; j++)
            cipherVector[j] = cipher[i + j] - 'a';

        int messageVector[3] = {0};
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                messageVector[x] += inverseKeyMatrix[x][y] * cipherVector[y];
                messageVector[x] %= 26;
            }
        }

        for (int j = 0; j < 3; j++)
            printf("%c", messageVector[j] + 'a');
    }
    printf("\n");
}

int main() {
    int keyMatrix[3][3];
    printf("Enter the 3x3 key matrix:\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &keyMatrix[i][j]);

    char message[100];
    printf("Enter the message to be encrypted (in lowercase): ");
    scanf("%s", message);
    int messageLength = strlen(message);

    while (messageLength % 3 != 0) {
        message[messageLength] = 'x';
        messageLength++;
    }

    hillEncrypt(keyMatrix, message, messageLength);

    char cipher[100];
    printf("Enter the cipher to be decrypted (in lowercase): ");
    scanf("%s", cipher);
    int cipherLength = strlen(cipher);

    hillDecrypt(keyMatrix, cipher, cipherLength);

    return 0;
}
