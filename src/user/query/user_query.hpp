#pragma once

#include <vector>
#include <optional>
#include "db.hpp"
#include "model/user_model.hpp"

/**
 * @class UserQueries
 * @brief Provides static methods for querying and managing user accounts.
 *
 * This class acts as a data-access layer for user-related operations,
 * including retrieving users by ID or email, creating accounts, and
 * fetching all users (admin-only).
 */
class UserQueries
{
public:
    /**
     * @brief Retrieve all users in the system.
     *
     * This function should only be used by administrators, as it exposes
     * all user records.
     *
     * @return A vector containing all User objects in the database.
     */
    static std::vector<User> getAllUsers();

    /**
     * @brief Retrieve a user by their unique identifier.
     *
     * @param userId The unique identifier of the user.
     * @return An optional User object. Contains a value if the user exists,
     *         otherwise empty.
     */
    static std::optional<User> getUserById(int userId);

    /**
     * @brief Retrieve a user by their email address.
     *
     * @param email The email address of the user.
     * @return An optional User object. Contains a value if the user exists,
     *         otherwise empty.
     */
    static std::optional<User> getUserByEmail(const std::string &email);

    /**
     * @brief Create a new user account.
     *
     * @param email The email address for the new account.
     * @param password The password for the new account.
     * @param type The type of user (e.g., NORMAL or ADMIN).
     * @param key The encryption key used for securing sensitive data.
     * @param iv The initialization vector used for encryption.
     * @return True if the account was successfully created, false otherwise.
     */
    static bool createAccount(const std::string &email, const std::string &password, const USER_TYPE &type, const std::string &key, const std::string &iv);
};