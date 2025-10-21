#include <iostream>
#include <sstream>

#include "utilities.hpp"

namespace Utilities
{
    void printHorizonatalLine(int length)
    {
        std::ostringstream ss;
        for (int i = 0; i < length; i++)
        {
            ss << "=";
        }
        std::cout << ss.str() << std::endl;
    }

    void printTextWithIndent(const char *value, int indent)
    {
        std::ostringstream ss;
        for (int i = 0; i < indent; i++)
        {
            ss << " ";
        }
        std::cout << ss.str() << value << std::endl;
    }

    void printLinePadding(int lineHeight)
    {
        std::ostringstream ss;
        for (int i = 0; i < lineHeight; i++)
        {
            ss << "\n";
        }
        std::cout << ss.str();
    }
}