#include <iostream>

#include "db.hpp"
#include "utilities.hpp"

#include "utilities/crypt/crypt.hpp"

EncryptedPayload encrypt(const std::string &text);
unsigned char *decrypt(const EncryptedPayload &encryptData);

int main()
{
    Utilities::printHorizonatalLine();

    Utilities::printTextWithIndent("🔒PASSLOCK🔒", 15);
    Utilities::printLinePadding();

    Utilities::printTextWithIndent("Password Manager System");

    auto enc = encrypt("JamesBond");
    std::cout << "Enc text: " << enc.ciphertext << "\n\n";
    std::cout << "Decrypted text: " << decrypt(enc) << std::endl;

    Utilities::printHorizonatalLine();
    DB::seedDB(); // Seeds database with tables

    return 0;
}