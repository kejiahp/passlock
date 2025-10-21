#pragma once

namespace Utilities
{
    // Generates a random password
    std::string randomPasswordGenerator(int length);
    // Checks if email is valid
    bool isEmail(const std::string &email);
    // Outputs an horizontal line to the console
    void printHorizonatalLine(int length = 50);
    // Outputs an indented text to the console
    void printTextWithIndent(const char *value, int indent = 10);
    // Outputs a number of new lines on the console
    void printLinePadding(int lineHeight = 1);
}