#include <iostream>

#include "utilities.hpp"
#include "credential_service.hpp"
#include "model/credential_model.hpp"
#include "query/credential_query.hpp"
#include "crypt/crypt.hpp"
#include "query/user_query.hpp"

void CredentialService::createCredentialService(const User &user)
{
    bool credentialNotCreated = true;
    std::string title;
    std::optional<std::string> email = std::nullopt, username = std::nullopt, password = std::nullopt, url = std::nullopt;

    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Add New Password");
    Utilities::printHorizonatalLine();

    while (credentialNotCreated)
    {
        Utilities::print("Enter Title: ");
        std::getline(std::cin, title);

        Utilities::fullTrim(title);

        if (title.length() <= 0)
        {
            std::cout << "Invalid Title" << std::endl;
            continue;
        }

        Utilities::print("Enter Email (optional, press enter to continue): ");
        std::getline(std::cin, *email);

        if (email.has_value())
        {
            Utilities::fullTrim(*email);

            if (!Utilities::isEmail(*email))
            {
                std::cout << "Invalid Email" << std::endl;
                continue;
            }
        }

        Utilities::print("Enter Username (optional, press enter to continue): ");
        std::getline(std::cin, *username);
        if (username.has_value())
        {
            Utilities::fullTrim(*username);

            if ((*username).length() <= 0)
            {
                std::cout << "Invalid Username" << std::endl;
                continue;
            }
        }

        Utilities::print("Enter Password (optional, press enter to continue): ");
        std::getline(std::cin, *password);
        if (password.has_value())
        {
            Utilities::fullTrim(*password);

            if ((*password).length() <= 0)
            {
                std::cout << "Invalid Password" << std::endl;
                continue;
            }
        }

        Utilities::print("Enter URL (optional, press enter to continue): ");
        std::getline(std::cin, *url);
        if (url.has_value())
        {
            Utilities::fullTrim(*url);

            if ((*url).length() <= 0)
            {
                std::cout << "Invalid URL" << std::endl;
                continue;
            }
        }

        if (password && (*password).length() >= 1)
        {
            password = Crypt::encryptAES128(*password, user.getIv(), user.getKey());
        }

        if (CredentialQueries::createCredential(user.getId(), title, email, username, password, url))
        {
            credentialNotCreated = false;
        }
        else
        {
            Utilities::print("Failed to add credential 🚫");
        }

        Utilities::print("Added Credential Successfully 🤗");
        std::cout << std::endl;
    }
}