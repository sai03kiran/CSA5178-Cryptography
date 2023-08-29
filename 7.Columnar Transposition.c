#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void columnarTranspositionEncrypt(const char *plaintext, const char *key) {
    int keyLength = strlen(key);
    int textLength = strlen(plaintext);
    
    int rows = (textLength + keyLength - 1) / keyLength;  // Calculate the number of rows
    
    char **grid = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (char *)malloc(keyLength * sizeof(char));
    }
    
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLength; j++) {
            if (index < textLength) {
                grid[i][j] = plaintext[index++];
            } else {
                grid[i][j] = 'X';  // Padding with 'X' if needed
            }
        }
    }
    
    // Sort the columns based on the key
    int *order = (int *)malloc(keyLength * sizeof(int));
    for (int i = 0; i < keyLength; i++) {
        order[i] = i;
    }
    for (int i = 0; i < keyLength - 1; i++) {
        for (int j = 0; j < keyLength - i - 1; j++) {
            if (key[j] > key[j + 1]) {
                char temp = key[j];
                key[j] = key[j + 1];
                key[j + 1] = temp;
                
                int tempOrder = order[j];
                order[j] = order[j + 1];
                order[j + 1] = tempOrder;
            }
        }
    }
    
    // Print the encrypted text
    printf("Encrypted Text: ");
    for (int i = 0; i < keyLength; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%c", grid[j][order[i]]);
        }
    }
    printf("\n");
    
    // Free memory
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
    free(order);
}
int main() {
    const char *plaintext = "HELLOWORLD";
    const char *key = "KEY";
    
    columnarTranspositionEncrypt(plaintext, key);
    
    return 0;
}

