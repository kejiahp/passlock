#include <regex>

#include "utilities.hpp"

namespace Utilities
{
    bool isEmail(const std::string &email)
    {
        const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return std::regex_match(email, pattern);
    }
}