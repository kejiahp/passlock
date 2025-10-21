#include <iostream>

#include "user_service.hpp"
#include "query/user_query.hpp"
#include "utilities.hpp"

void UserService::createUserService()
{
    std::string email, password, type, key;
    std::cout << "Enter Email: ";
    std::cin >> email;
    Utilities::printLinePadding();
    if (!Utilities::isEmail(email))
    {
        std::cout << "Invalid Email\n";
    }

    // Validate password or generate a random password
    std::cout << "Enter Password: ";
    std::cin >> password;
    Utilities::printLinePadding();

    // Validate Type (Normal or Admin)
    std::cout << "Enter Type: ";
    std::cin >> type;
    Utilities::printLinePadding();

    // Generate Key
    // Utilities::generateKey()

    // check for existing user with the same email
    // UserQueries::createAccount()
};

// User UserService::loginUserService() {

// };