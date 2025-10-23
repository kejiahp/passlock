#include <iostream>

#include "user_service.hpp"
#include "query/user_query.hpp"
#include "utilities.hpp"

void UserService::createUserService()
{
    std::string email, password, type = "NORMAL", key;

    Utilities::print("Enter Email: ");
    std::cin >> email;

    if (!Utilities::isEmail(email))
    {
        std::cout << "Invalid Email\n";
    }

    // Validate password or generate a random password
    Utilities::print("Enter Password (Press G to generate a random password): ");
    std::cin >> password;

    // Generate Key
    // Utilities::generateKey()

    // check for existing user with the same email
    // UserQueries::createAccount()
};

// User UserService::loginUserService() {

// };