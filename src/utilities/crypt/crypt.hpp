#pragma once

#include <string>

/**
 * @namespace Crypt
 * @brief Provides cryptographic utility functions for encoding, encryption, and hashing.
 *
 * This namespace contains helper functions for converting between binary and hex,
 * generating random values, performing AES-128 encryption/decryption, and hashing
 * with SHA-256.
 */
namespace Crypt
{
    /**
     * @brief Convert binary data to a hexadecimal string.
     *
     * @param data The binary data as a vector of unsigned chars.
     * @return A string containing the hexadecimal representation of the input data.
     */
    std::string toHex(const std::vector<unsigned char> &data);

    /**
     * @brief Convert a hexadecimal string to binary data.
     *
     * @param hex The hexadecimal string to convert.
     * @return A vector of unsigned chars representing the binary data.
     */
    std::vector<unsigned char> fromHex(const std::string &hex);

    /**
     * @brief Generate a random 128-bit (16-byte) value and return it as a hex string.
     *
     * @return A string containing the generated 128-bit random value in hexadecimal format.
     */
    std::string generate128BitHex();

    /**
     * @brief Encrypt plaintext using AES-128 in Cipher Block Chaining (CBC) mode.
     *
     * @param plaintext The input string to encrypt.
     * @param hexKey The encryption key in hexadecimal format (128-bit).
     * @param hexIV The initialization vector in hexadecimal format (128-bit).
     * @return A string containing the ciphertext in hexadecimal format.
     */
    std::string encryptAES128(const std::string &plaintext, const std::string &hexKey, const std::string &hexIV);

    /**
     * @brief Decrypt ciphertext using AES-128 in Cipher Block Chaining (CBC) mode.
     *
     * @param hexCiphertext The ciphertext in hexadecimal format.
     * @param hexKey The decryption key in hexadecimal format (128-bit).
     * @param hexIV The initialization vector in hexadecimal format (128-bit).
     * @return The decrypted plaintext string.
     */
    std::string decryptAES128(const std::string &hexCiphertext, const std::string &hexKey, const std::string &hexIV);

    /**
     * @brief Compute the SHA-256 hash of a string.
     *
     * @param str The input string to hash.
     * @return A string containing the SHA-256 hash in hexadecimal format.
     */
    std::string hashSHA256(const std::string &str);
}