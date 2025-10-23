#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <vector>
#include <iostream>

#include "crypt.hpp"

// Ensure the function is only accessible within this file
static void handleErrors()
{
    // `ERR_print_errors_fp` from openssl, attempts to write to a file. Here we overwrite the default file handler with `stderr` then writing to the console.
    ERR_print_errors_fp(stderr);
    // Forcefully terminate the program
    abort();
}

// Encrypt a plaintext using AES-128 bit
int aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, ciphertext_len;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        handleErrors();
    }

    if (!EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {
        handleErrors();
    }
    ciphertext_len = len;

    if (!EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        handleErrors();
    }

    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

// Decrypt a plaintext using AES-128 bit
int aes_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if (!EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

void generate128BitHex(unsigned char *IV)
{
    if (RAND_bytes(IV, sizeof(IV)) != 1)
    {
        handleErrors();
    };
}

std::string bytesToBase64String(const unsigned char *iv, size_t length)
{
    unsigned char encoded[EVP_ENCODE_LENGTH(length)];
    int outlen = EVP_EncodeBlock(encoded, iv, length);
    return std::string(reinterpret_cast<char *>(encoded), outlen);
}

std::vector<unsigned char> base64ToBytes(const std::string &base64)
{
    size_t len = base64.length();
    std::vector<unsigned char> decoded(len); // Allocate enough space

    int outlen = EVP_DecodeBlock(decoded.data(),
                                 reinterpret_cast<const unsigned char *>(base64.c_str()),
                                 len);

    if (outlen < 0)
        throw std::runtime_error("Base64 decoding failed");

    // Remove padding bytes if needed
    while (!decoded.empty() && decoded.back() == '\0')
    {
        decoded.pop_back();
    }

    return decoded;
}

EncryptedPayload encrypt(const std::string &text)
{
    unsigned char key[16];
    generate128BitHex(key);
    unsigned char iv[16];
    generate128BitHex(iv);
    unsigned char ciphertext[128];

    // convert string to unsigned char[]
    std::vector<unsigned char> plaintextVector(text.c_str(), text.c_str() + text.size() + 1);
    unsigned char *plaintext = plaintextVector.data();

    int ciphertext_len = aes_encrypt(plaintext, text.size(), key, iv, ciphertext);

    std::string keyString = bytesToBase64String(key, sizeof(key));
    std::string ivString = bytesToBase64String(iv, sizeof(iv));
    std::string ciphertextString = bytesToBase64String(ciphertext, sizeof(ciphertext));
    return EncryptedPayload{keyString, ivString, ciphertextString};
}

unsigned char *decrypt(const EncryptedPayload &encryptData)
{
    unsigned char decryptedtext[128];
    std::vector<unsigned char> cipherChar = base64ToBytes(encryptData.ciphertext);
    std::vector<unsigned char> keyChar = base64ToBytes(encryptData.key);
    std::vector<unsigned char> ivChar = base64ToBytes(encryptData.iv);
    int decryptedtext_len = aes_decrypt(cipherChar.data(), cipherChar.size(), keyChar.data(), ivChar.data(), decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';

    return decryptedtext;
}