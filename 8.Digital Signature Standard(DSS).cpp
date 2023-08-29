#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int main() {
    // Initialize the OpenSSL library
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Generate RSA key pair
    RSA *rsa_key = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if (!rsa_key) {
        fprintf(stderr, "Error generating RSA key pair\n");
        return 1;
    }

    // Message to be signed
    const char *message = "Hello, digital signature!";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Hash the message
    SHA256((const unsigned char *)message, strlen(message), hash);

    // Sign the hash
    unsigned char signature[RSA_size(rsa_key)];
    unsigned int signature_length;
    int sign_result = RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &signature_length, rsa_key);
    if (sign_result != 1) {
        fprintf(stderr, "Error signing the data\n");
        return 1;
    }

    // Verify the signature
    int verify_result = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, signature_length, rsa_key);
    if (verify_result != 1) {
        fprintf(stderr, "Signature verification failed\n");
        return 1;
    } else {
        printf("Signature verified successfully!\n");
    }

    // Clean up
    RSA_free(rsa_key);
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

    return 0;
}

