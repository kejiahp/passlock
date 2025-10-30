#include <iostream>

#include "user_service.hpp"
#include "query/user_query.hpp"
#include "utilities.hpp"
#include "crypt/crypt.hpp"
#include "model/user_model.hpp"

void UserService::getAllUsersService(const User &user)
{
    if (!user.isAdmin())
    {
        std::cout << "Unauthorized Access" << std::endl;
        return;
    }

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("View all Users");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    std::vector<User> users = UserQueries::getAllUsers();

    if (users.empty())
    {
        std::cout << "No Users to Display" << std::endl;
        return;
    }

    for (auto user : users)
    {
        std::cout << user.toString() << "\n";
    }
    std::cout << std::endl;
}

void UserService::deleteUserByIdService(const User &user)
{
    if (!user.isAdmin())
    {
        std::cout << "Unauthorized Access" << std::endl;
        return;
    }

    bool userNotDeleted = true;
    std::string userIdStr, deleteConfirmation;
    int userId;

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Delete User");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    while (userNotDeleted)
    {
        Utilities::print("Enter ID of user to delete: ");
        std::getline(std::cin, userIdStr);

        Utilities::fullTrim(userIdStr);

        if (userIdStr.length() <= 0)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        try
        {
            userId = std::stoi(userIdStr);
        }
        catch (std::exception &e)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        auto userExist = UserQueries::getUserById(userId);

        if (!userExist)
        {
            std::cout << "User with ID: " << userId << " does not exist." << std::endl;
            continue;
        }

        Utilities::print("Are you sure you want to delete this user? (Y/n): ");
        std::getline(std::cin, deleteConfirmation);

        if (deleteConfirmation != "Y" && deleteConfirmation != "y")
        {
            return;
        }

        if (UserQueries::deleteUserById(userId))
        {
            userNotDeleted = false;
        }
        else
        {
            Utilities::print("Failed to delete user 🚫");
        }
    }

    Utilities::print("Deleted User Successfully 🤗 ");
    std::cout << std::endl;
}

void UserService::updateUserDetailsService(const User &user)
{
    if (!user.isAdmin())
    {
        std::cout << "Unauthorized Access" << std::endl;
        return;
    }

    bool userNotUpdated = true;
    std::string userIdStr;
    int userId;
    std::optional<std::string> email, password, type;

    type.emplace();
    email.emplace();
    password.emplace();

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Update User details");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    while (userNotUpdated)
    {
        Utilities::print("Enter ID of user to update: ");
        std::getline(std::cin, userIdStr);

        Utilities::fullTrim(userIdStr);

        if (userIdStr.length() <= 0)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        try
        {
            userId = std::stoi(userIdStr);
        }
        catch (std::exception &e)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        auto userExist = UserQueries::getUserById(userId);

        if (!userExist)
        {
            std::cout << "User with ID: " << userId << " does not exist." << std::endl;
            continue;
        }

        Utilities::print("Enter New Email (optional, press enter to continue): ");
        std::getline(std::cin, *email);
        if ((*email).empty())
            email = std::nullopt;
        if (email.has_value())
        {
            Utilities::fullTrim(*email);
            if (!Utilities::isEmail(*email))
            {
                std::cout << "Invalid Email" << std::endl;
                continue;
            }
        }

        Utilities::print("Enter New Type [NORMAL or ADMIN] (optional, press enter to continue): ");
        std::getline(std::cin, *type);
        if ((*type).empty())
            type = std::nullopt;
        if (type.has_value())
        {
            Utilities::fullTrim(*type);
            if (*type != "NORMAL" && *type != "ADMIN")
            {
                std::cout << "Allowed types are `NORMAL` and `ADMIN`" << std::endl;
                continue;
            }
        }

        Utilities::print("Enter New Password (optional, press enter to continue): ");
        std::getline(std::cin, *password);
        if (password->empty())
            password = std::nullopt;
        if (password.has_value())
        {
            Utilities::fullTrim(*password);

            if (password->length() <= 0)
            {
                std::cout << "Invalid Password" << std::endl;
                continue;
            }
        }

        if (password && password->length() >= 1)
        {
            password = Crypt::hashSHA256(*password);
        }

        if (UserQueries::updateUserDetails(userId, email, type, password))
        {
            userNotUpdated = false;
        }
        else
        {
            Utilities::print("Failed to update user 🚫 ");
        }

        Utilities::print("Updated User Successfully 🤗 ");
        std::cout << std::endl;
    }
}

void UserService::createUserService()
{
    bool accountNotCreated = true;
    std::string email, password, type = "NORMAL", key, iv;

    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Account Creation - No spaces allowed🚫");
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

        if (password.length() == 1 && password == "G")
        {
            password = Utilities::randomPasswordGenerator(20);
            std::cout << "Your generated password is: " << password << std::endl;
        }

        // Attempts to erase whitespaces from the password
        Utilities::fullTrim(password);

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
        std::string passwordHash = Crypt::hashSHA256(password);

        if (UserQueries::createAccount(
                email,
                passwordHash,
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

    Utilities::print("Account Created Successfully 🤗 ");
    std::cout << std::endl;
};

User UserService::loginUserService()
{

    std::optional<User> authUser = std::nullopt;
    std::string email, password;

    // accept and validate email

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Account Login - No spaces allowed🚫");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    while (authUser.has_value() == false)
    {
        Utilities::print("Enter Email: ");
        std::getline(std::cin, email);

        if (!Utilities::isEmail(email))
        {
            std::cout << "Invalid Email" << std::endl;
            continue;
        }

        auto userWithEmail = UserQueries::getUserByEmail(email);

        // check for existing user with the same email
        if (!userWithEmail)
        {
            Utilities::print("Account with email " + email + " does not exist in the system.");
            std::cout << std::endl;
            continue;
        }

        Utilities::print("Enter Password: ");
        std::getline(std::cin, password);

        std::string hashpassword = Crypt::hashSHA256(password);

        // match hashed passwords
        if (userWithEmail->getPassword() != hashpassword)
        {
            Utilities::print("Invalid credentials");
            std::cout << std::endl;
            continue;
        }

        authUser = userWithEmail.value();
    }

    return authUser.value();
};