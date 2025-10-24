#include <iostream>

#include "db.hpp"
#include "utilities.hpp"

#include "utilities/crypt/crypt.hpp"
#include "user/service/user_service.hpp"

class MainApplication
{
public:
    static void start()
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
            }
            else
            {
                Utilities::print("Invalid Input");
                std::cout << std::endl;
            }
        }
    }
};

int main()
{
    MainApplication::start();

    return 0;
}