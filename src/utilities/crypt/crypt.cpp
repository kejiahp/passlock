#include <vector>
#include <sstream>
#include <iostream>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#include "crypt.hpp"
#include <iomanip>

// Ensure the function is only accessible within this file
static void handleErrors()
{
    // `ERR_print_errors_fp` from openssl, attempts to write to a file. Here we overwrite the default file handler with `stderr` then writing to the console.
    ERR_print_errors_fp(stderr);
    // Forcefully terminate the program
    abort();
}

namespace Crypt
{

    std::string toHex(const std::vector<unsigned char> &data)
    {
        std::ostringstream oss;
        for (unsigned char byte : data)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
        }
        return oss.str();
    }

    std::vector<unsigned char> fromHex(const std::string &hex)
    {
        std::vector<unsigned char> data;
        for (size_t i = 0; i < hex.length(); i += 2)
        {
            std::string byteString = hex.substr(i, 2);
            unsigned char byte = (unsigned char)strtol(byteString.c_str(), nullptr, 16);
            data.push_back(byte);
        }
        return data;
    }

    std::string generate128BitHex()
    {
        std::vector<unsigned char> buffer(16);
        if (RAND_bytes(buffer.data(), buffer.size()) != 1)
        {
            handleErrors();
        };
        return toHex(buffer);
    }

    std::string encryptAES128(const std::string &plaintext, const std::string &hexKey, const std::string &hexIV)
    {
        std::vector<unsigned char> key = fromHex(hexKey);
        std::vector<unsigned char> iv = fromHex(hexIV);
        std::vector<unsigned char> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);

        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        int len = 0, ciphertext_len = 0;

        if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.data(), iv.data()))
        {
            handleErrors();
        }
        if (!EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char *>(plaintext.c_str()), plaintext.length()))
        {
            handleErrors();
        }
        ciphertext_len = len;
        if (!EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
        {
            handleErrors();
        }
        ciphertext_len += len;

        EVP_CIPHER_CTX_free(ctx);
        ciphertext.resize(ciphertext_len);
        return toHex(ciphertext);
    }

    std::string decryptAES128(const std::string &hexCiphertext, const std::string &hexKey, const std::string &hexIV)
    {
        std::vector<unsigned char> key = fromHex(hexKey);
        std::vector<unsigned char> iv = fromHex(hexIV);
        std::vector<unsigned char> ciphertext = fromHex(hexCiphertext);
        std::vector<unsigned char> plaintext(ciphertext.size());

        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        int len = 0, plaintext_len = 0;

        if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.data(), iv.data()))
        {
            handleErrors();
        }
        if (!EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()))
        {
            handleErrors();
        }
        plaintext_len = len;
        if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
        {
            handleErrors();
        }
        plaintext_len += len;

        EVP_CIPHER_CTX_free(ctx);
        plaintext.resize(plaintext_len);
        return std::string(plaintext.begin(), plaintext.end());
    }

    std::string hashSHA256(const std::string &text)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char *>(text.c_str()), text.size(), hash);

        size_t size = sizeof(hash) / sizeof(hash[0]);
        std::vector<unsigned char> hashVec(hash, hash + size);

        return toHex(hashVec);
    }

}