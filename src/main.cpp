#include <iostream>

#include "db.hpp"
#include "utilities.hpp"

#include "utilities/crypt/crypt.hpp"
#include "user/service/user_service.hpp"
#include "user/model/user_model.hpp"
#include "credential/service/credential_service.hpp"

// Main application singleton
// Ensuring there is only one instance of the application live at anytime.
class MainApplication
{
private:
    std::optional<User> userSession = std::nullopt;

    MainApplication() = default;
    ~MainApplication() = default;
    MainApplication(const MainApplication &) = delete;
    MainApplication &operator=(const MainApplication &) = delete;

public:
    static MainApplication &getInstance()
    {
        static MainApplication instance;
        return instance;
    }

    void start()
    {
        DB::seedDB(); // Seeds database with tables, ensure database exist on program start up

        Utilities::printHorizonatalLine();

        Utilities::printTextWithIndent("🔒PASSLOCK🔒", 15);
        Utilities::printLinePadding();

        Utilities::printTextWithIndent("Password Manager System");

        Utilities::printHorizonatalLine();
        Utilities::printLinePadding();

        // Landing Console Outputs
        std::string cmd = "\0"; // null terminator

        while (cmd == "\0")
        {
            Utilities::print("[1] Account Creation\n");
            Utilities::print("[2] Account Login\n");

            Utilities::printLinePadding();

            Utilities::print("Enter your choice: ");
            std::getline(std::cin, cmd);

            if (cmd == "1")
            {
                UserService::createUserService();
            }
            else if (cmd == "2")
            {
                userSession = UserService::loginUserService();
                mainMenu();
            }
            else
            {
                Utilities::print("Invalid Input");
                std::cout << std::endl;
            }
        }
    }

private:
    void mainMenu()
    {
        if (!userSession)
        {
            std::cout << "Unauthenticated User 🚫" << std::endl;
        }

        Utilities::printLinePadding();

        Utilities::printHorizonatalLine();
        Utilities::print("Welcome to your Main Menu, " + userSession->getEmail() + "\n");
        Utilities::printHorizonatalLine();

        std::string cmd = "\0"; // null terminator

        while (true)
        {
            Utilities::printLinePadding();

            Utilities::print("[1] Add New Password\n");
            Utilities::print("[2] View Password\n");
            Utilities::print("[3] Search Password\n");
            Utilities::print("[4] Update Password\n");
            Utilities::print("[5] Delete Password\n");
            Utilities::print("[6] Logout / Exit\n");

            Utilities::printLinePadding();

            Utilities::print("Enter your choice: ");
            std::getline(std::cin, cmd);

            if (cmd == "1")
            {
                CredentialService::createCredentialService(*userSession);
            }
            else if (cmd == "2")
            {
                CredentialService::viewUserCredentialService(*userSession);
            }
            else if (cmd == "3")
            {
                CredentialService::searchCredentialService(*userSession);
            }
            else if (cmd == "4")
            {
                CredentialService::updateCredentialService(*userSession);
            }
            else if (cmd == "5")
            {
                CredentialService::deleteCredentialService(*userSession);
            }
            else if (cmd == "6")
            {
                logout();
                return;
            }
            else
            {
                Utilities::print("Invalid Input");
                std::cout << std::endl;
            }
        }
    }

    void logout()
    {
        userSession = std::nullopt;
    }
};

int main()
{
    MainApplication::getInstance().start();

    return 0;
}