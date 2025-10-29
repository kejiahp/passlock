#include <iostream>

#include "db.hpp"
#include "utilities.hpp"

#include "utilities/crypt/crypt.hpp"
#include "user/service/user_service.hpp"
#include "user/model/user_model.hpp"
#include "credential/service/credential_service.hpp"

/**
 * @class MainApplication
 * @brief Singleton class representing the main entry point of the application.
 *
 * This class ensures that only one instance of the application exists at any time.
 * It manages the user session, initializes the database, and provides the main
 * console-based user interface for account and credential management.
 */
class MainApplication
{
private:
    /**
     * @brief Holds the currently authenticated user session.
     *
     * If no user is logged in, this remains std::nullopt.
     */
    std::optional<User> userSession = std::nullopt;

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    MainApplication() = default;

    /**
     * @brief Private destructor to enforce singleton pattern.
     */
    ~MainApplication() = default;
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    MainApplication(const MainApplication &) = delete;

    /**
     * @brief Deleted assignment operator to prevent copying.
     */
    MainApplication &operator=(const MainApplication &) = delete;

public:
    /**
     * @brief Retrieve the singleton instance of MainApplication.
     *
     * @return Reference to the single MainApplication instance.
     */
    static MainApplication &getInstance()
    {
        static MainApplication instance;
        return instance;
    }

    /**
     * @brief Start the application.
     *
     * Initializes the database, displays the landing menu, and handles
     * user input for account creation or login.
     */
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
    /**
     * @brief Display the main menu for authenticated users.
     *
     * Provides options for managing credentials, including creating,
     * viewing, searching, updating, and deleting, as well as logging out.
     */
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

    /**
     * @brief Log out the current user.
     *
     * Clears the user session and returns to the landing menu.
     */
    void logout()
    {
        userSession = std::nullopt;
    }
};

/**
 * @brief Program entry point.
 *
 * Initializes and starts the MainApplication singleton.
 *
 * @return Exit status code (0 for success).
 */
int main()
{
    MainApplication::getInstance().start();

    return 0;
}