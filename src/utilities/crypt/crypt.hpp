#include <string>

namespace Crypt
{
    // Convert binary data to hex string
    std::string toHex(const std::vector<unsigned char> &data);

    // Convert hex string to binary data
    std::vector<unsigned char> fromHex(const std::string &hex);

    // Generate 128-bit (16-byte) random value and return as hex string
    std::string generate128BitHex();

    // Encrypt a plaintext using AES-128-Cipher Block Chaining mode(CBC)
    std::string encryptAES128(const std::string &plaintext, const std::string &hexKey, const std::string &hexIV);

    // Decrypt a ciphertext using AES-128-Cipher Block Chaining mode(CBC)
    std::string decryptAES128(const std::string &hexCiphertext, const std::string &hexKey, const std::string &hexIV);

    // Hashing a text using SHA256
    std::string hashSHA256(const std::string &str);
}