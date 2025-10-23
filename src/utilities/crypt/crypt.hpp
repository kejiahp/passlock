#include <string>

struct EncryptedPayload
{
    const std::string key;
    const std::string iv;
    const std::string ciphertext;

    EncryptedPayload(std::string key, std::string IV, std::string cipherText) : key(key), iv(IV), ciphertext(cipherText) {}
};