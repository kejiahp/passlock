#include <iostream>
#include <utilities.hpp>

namespace Utilities
{

    void utilitiesMain()
    {
        std::cout << "UtilitiesMain\n";
        std::cout << Utilities::randomPasswordGenerator(10) << std::endl;
    }
}