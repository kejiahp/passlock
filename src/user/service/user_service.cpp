#include <iostream>

#include "user_service.hpp"
#include "query/user_query.hpp"
#include "utilities.hpp"
#include "crypt/crypt.hpp"
#include "model/user_model.hpp"

void UserService::createUserService()
{
    bool accountNotCreated = true;
    std::string email, password, type = "NORMAL", key, iv;

    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Create an Account - No spaces allowed🚫");
    Utilities::printHorizonatalLine();

    while (accountNotCreated)
    {
        Utilities::print("Enter Email: ");
        std::getline(std::cin, email);

        if (!Utilities::isEmail(email))
        {
            std::cout << "Invalid Email" << std::endl;
            continue;
        }

        auto isEmailExist = UserQueries::getUserByEmail(email);

        // check for existing user with the same email
        if (isEmailExist)
        {
            Utilities::print("A user with email " + email + " already exists, Try another one.");
            std::cout << std::endl;
            continue;
        }

        // Validate password or generate a random password
        Utilities::print("Enter Password (Enter only G to generate a random password): ");
        std::getline(std::cin, password);

        std::cout << "password: " << password << std::endl;

        if (password.length() == 1 && password == "G")
        {
            password = Utilities::randomPasswordGenerator(20);
            std::cout << "Your generated password is: " << password << std::endl;
        }

        // Attempts to erase whitespaces from the password
        // Utilities::fullTrim(password);

        if (password.length() < 10)
        {
            Utilities::print("Password must be 10 characters or more");
            std::cout << std::endl;
            continue;
        }

        // Generate a unique encryption/decryption key for each user
        key = Crypt::generate128BitHex();
        // Generate a unique encryption/decryption initial vector (iv) for each user
        iv = Crypt::generate128BitHex();
        // encrypt users password
        std::string passwordCipher = Crypt::encryptAES128(password, key, iv);

        if (UserQueries::createAccount(
                email,
                passwordCipher,
                USER_TYPE_FromString(type),
                key,
                iv))
        {
            accountNotCreated = false;
        }
        else
        {
            Utilities::print("Failed to create an account 🚫");
        }
    }

    Utilities::print("Account Created Successfully 🤗");
    std::cout << std::endl;
};

User UserService::loginUserService() {

};