#include <iostream>
#include <utilities.hpp>

void userMain();

int main()
{
    std::cout << "Hello World MAIN\n";

    userMain();
    Utilities::utilitiesMain();

    std::cout << "Hello World MAIN\n";
    return 0;
}