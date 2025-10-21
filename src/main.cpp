#include <iostream>

#include "db.hpp"
#include "utilities.hpp"

int main()
{
    Utilities::printHorizonatalLine();

    Utilities::printTextWithIndent("🔒PASSLOCK🔒", 15);
    Utilities::printLinePadding();

    Utilities::printTextWithIndent("Password Manager System");

    Utilities::printHorizonatalLine();
    DB::seedDB(); // Seeds database with tables

    return 0;
}