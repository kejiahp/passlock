#include <iostream>

#include "utilities.hpp"
#include "credential_service.hpp"
#include "model/credential_model.hpp"
#include "query/credential_query.hpp"
#include "crypt/crypt.hpp"
#include "query/user_query.hpp"

void CredentialService::getAllCredentialService(const User &user)
{
    if (!user.isAdmin())
    {
        std::cout << "Unauthorized Access" << std::endl;
        return;
    }

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("View all Credentials");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    std::vector<Credential> credentials = CredentialQueries::getAllCredentials();

    if (credentials.empty())
    {
        std::cout << "No Credentials to Display" << std::endl;
        return;
    }

    for (auto cred : credentials)
    {
        std::cout << cred.toShortString() << "\n";
    }
    std::cout << std::endl;
}

void CredentialService::createCredentialService(const User &user)
{
    bool credentialNotCreated = true;
    std::string title;
    std::optional<std::string> email, username, password, url;

    email.emplace();
    username.emplace();
    password.emplace();
    url.emplace();

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Add New Password");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

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

        Utilities::print("Enter Username (optional, press enter to continue): ");
        std::getline(std::cin, *username);
        if ((*username).empty())
            username = std::nullopt;
        if (username.has_value())
        {
            Utilities::fullTrim(*username);

            if (username->length() <= 0)
            {
                std::cout << "Invalid Username" << std::endl;
                continue;
            }
        }

        Utilities::print("Enter Password (optional, press enter to continue): ");
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

        Utilities::print("Enter URL (optional, press enter to continue): ");
        std::getline(std::cin, *url);
        if (url->empty())
            url = std::nullopt;
        if (url.has_value())
        {
            Utilities::fullTrim(*url);

            if (url->length() <= 0)
            {
                std::cout << "Invalid URL" << std::endl;
                continue;
            }
        }

        if (password && password->length() >= 1)
        {
            password = Crypt::encryptAES128(*password, user.getKey(), user.getIv());
        }

        if (CredentialQueries::createCredential(user.getId(), title, email, username, password, url))
        {
            credentialNotCreated = false;
        }
        else
        {
            Utilities::print("Failed to add credential 🚫");
        }

        Utilities::print("Added Credential Successfully 🤗 ");
        std::cout << std::endl;
    }
}

void CredentialService::viewUserCredentialService(const User &user)
{
    std::string revealPassword;
    bool showPassword = false;

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("View Password");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    Utilities::print("Reveal passwords as plaintext? (Y/n): ");
    std::getline(std::cin, revealPassword);

    if (revealPassword == "Y" || revealPassword == "y")
    {
        showPassword = true;
    }
    else
    {
        showPassword = false;
    }

    std::vector<Credential> credentials = CredentialQueries::getCredentialsByUserId(user.getId());

    if (credentials.empty())
    {
        std::cout << "No Credentials to Display" << std::endl;
        return;
    }

    // if the reveal option was selected pass an optional `RevealCredentialProps` to `toString` else just pass a null value
    auto reveal = showPassword ? std::make_optional(RevealCredentialProps{user.getIv(), user.getKey()}) : std::nullopt;

    for (auto cred : credentials)
    {
        std::cout << cred.toString(reveal) << "\n\n";
    }
    std::cout << std::endl;
}

void CredentialService::searchCredentialService(const User &user)
{
    std::string searchQuery;
    bool isNotSearchComplete = true;

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Search Password");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    while (isNotSearchComplete)
    {
        Utilities::print("Enter title to search for: ");
        std::getline(std::cin, searchQuery);

        Utilities::fullTrim(searchQuery);

        if (searchQuery.empty())
        {
            std::cout << "Invalid search query" << std::endl;
            continue;
        }

        std::vector<Credential> credentials = CredentialQueries::searchCredentialById(user.getId(), searchQuery);

        if (credentials.empty())
        {
            std::cout << "No Credentials match the search query: `" << searchQuery << "`" << std::endl;
            return;
        }

        for (auto cred : credentials)
        {
            std::cout << cred.toString() << "\n\n";
        }
        std::cout << std::endl;
        isNotSearchComplete = false;
    }
}

void CredentialService::updateCredentialService(const User &user)
{
    bool credentialNotUpdated = true;
    std::string credentialIdStr;
    int credentialId;
    std::optional<std::string> title, email, username, password, url;

    title.emplace();
    email.emplace();
    username.emplace();
    password.emplace();
    url.emplace();

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Update Password");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    auto credential = CredentialQueries::getCredentialsByUserId(user.getId());

    Utilities::print("Your Passwords");
    Utilities::printHorizonatalLine(10);

    if (credential.empty())
    {
        std::cout << "No Credentials to Display" << std::endl;
        return;
    }

    for (auto cred : credential)
    {
        std::cout << cred.toShortString() << "\n";
    }
    std::cout << std::endl;

    while (credentialNotUpdated)
    {
        Utilities::print("Enter ID of password to update: ");
        std::getline(std::cin, credentialIdStr);

        Utilities::fullTrim(credentialIdStr);

        if (credentialIdStr.length() <= 0)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        try
        {
            credentialId = std::stoi(credentialIdStr);
        }
        catch (std::exception &e)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        auto credentialExist = CredentialQueries::getCredentialById(credentialId, user.getId());

        if (!credentialExist)
        {
            std::cout << "Credential with ID: " << credentialId << " does not exist." << std::endl;
            continue;
        }

        Utilities::print("Enter New Title (optional, press enter to continue): ");
        std::getline(std::cin, *title);
        if ((*title).empty())
            title = std::nullopt;
        if (title.has_value())
        {
            Utilities::fullTrim(*title);
            if (title->length() <= 0)
            {
                std::cout << "Invalid Title" << std::endl;
                continue;
            }
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

        Utilities::print("Enter New Username (optional, press enter to continue): ");
        std::getline(std::cin, *username);
        if ((*username).empty())
            username = std::nullopt;
        if (username.has_value())
        {
            Utilities::fullTrim(*username);

            if (username->length() <= 0)
            {
                std::cout << "Invalid Username" << std::endl;
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

        Utilities::print("Enter New URL (optional, press enter to continue): ");
        std::getline(std::cin, *url);
        if (url->empty())
            url = std::nullopt;
        if (url.has_value())
        {
            Utilities::fullTrim(*url);

            if (url->length() <= 0)
            {
                std::cout << "Invalid URL" << std::endl;
                continue;
            }
        }

        if (password && password->length() >= 1)
        {
            password = Crypt::encryptAES128(*password, user.getKey(), user.getIv());
        }

        if (CredentialQueries::updateCredential(credentialId, user.getId(), title, email, username, password, url))
        {
            credentialNotUpdated = false;
        }
        else
        {
            Utilities::print("Failed to update credential 🚫");
        }

        Utilities::print("Updated Credential Successfully 🤗 ");
        std::cout << std::endl;
    }
}

void CredentialService::deleteCredentialService(const User &user)
{
    bool credentialNotDeleted = true;
    std::string credentialIdStr, deleteConfirmation;
    int credentialId;

    Utilities::printLinePadding();
    Utilities::printHorizonatalLine();
    Utilities::printTextWithIndent("Delete Password");
    Utilities::printHorizonatalLine();
    Utilities::printLinePadding();

    while (credentialNotDeleted)
    {
        Utilities::print("Enter ID of password to delete: ");
        std::getline(std::cin, credentialIdStr);

        Utilities::fullTrim(credentialIdStr);

        if (credentialIdStr.length() <= 0)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        try
        {
            credentialId = std::stoi(credentialIdStr);
        }
        catch (std::exception &e)
        {
            std::cout << "Invalid ID" << std::endl;
            continue;
        }

        auto credentialExist = CredentialQueries::getCredentialById(credentialId, user.getId());

        if (!credentialExist)
        {
            std::cout << "Credential with ID: " << credentialId << " does not exist." << std::endl;
            continue;
        }

        Utilities::print("Are you sure you want to delete this password? (Y/n): ");
        std::getline(std::cin, deleteConfirmation);

        if (deleteConfirmation != "Y" && deleteConfirmation != "y")
        {
            return;
        }

        if (
            CredentialQueries::deleteCredentialById(credentialId, user.getId()))
        {
            credentialNotDeleted = false;
        }
        else
        {
            Utilities::print("Failed to delete credential 🚫");
        }
    }

    Utilities::print("Deleted Credential Successfully 🤗 ");
    std::cout << std::endl;
}