#pragma once

/**
 * @namespace Utilities
 * @brief Provides helper functions for string manipulation, validation,
 *        random generation, and console output formatting.
 */
namespace Utilities
{
    /**
     * @brief Generates a random password of the specified length.
     *
     * @param length The desired length of the password (default is 10).
     * @return A randomly generated password string.
     */
    std::string randomPasswordGenerator(int length = 10);

    /**
     * @brief Checks if a given string is a valid email address.
     *
     * @param email The string to validate.
     * @return True if the string is a valid email format, false otherwise.
     */
    bool isEmail(const std::string &email);

    /**
     * @brief Removes all whitespace characters from a string.
     *
     * @param text The string to be trimmed. Modified in place.
     */
    void fullTrim(std::string &text);

    /**
     * @brief Outputs a horizontal line to the console.
     *
     * @param length The number of characters in the line (default is 50).
     */
    void printHorizonatalLine(int length = 50);

    /**
     * @brief Outputs indented text to the console.
     *
     * @param value The text to print.
     * @param indent The number of spaces to indent before the text (default is 10).
     */
    void printTextWithIndent(const char *value, int indent = 10);

    /**
     * @brief Outputs a number of blank lines to the console.
     *
     * @param lineHeight The number of new lines to print (default is 1).
     */
    void printLinePadding(int lineHeight = 1);

    /**
     * @brief Outputs the given text to the console.
     *
     * @param text The string to print.
     */
    void print(const std::string &text);
}