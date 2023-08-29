#include <stdio.h>
#include <string.h>
#include <ctype.h>
void vigenereEncrypt(char *key, char *message) {
    int keyLength = strlen(key);
    int messageLength = strlen(message);

    printf("Encrypted message: ");

    for (int i = 0, j = 0; i < messageLength; i++) {
        char currentChar = message[i];
        
        if (isalpha(currentChar)) {
            int keyShift = tolower(key[j % keyLength]) - 'a';
            char encryptedChar;

            if (isupper(currentChar)) {
                encryptedChar = (currentChar - 'A' + keyShift) % 26 + 'A';
            } else {
                encryptedChar = (currentChar - 'a' + keyShift) % 26 + 'a';
            }


            printf("%c", encryptedChar);
            j++;
        } else {
            printf("%c", currentChar);
        }
    }
    printf("\n"); 
}
int main() {
    char key[100];
    char message[100];

    printf("Enter the key (alphabetic characters only): ");
    scanf("%s", key);

    printf("Enter the message to be encrypted: ");
    scanf(" %[^\n]s", message);

    vigenereEncrypt(key, message);

    return 0;
}
