#pragma once

#include "model/user_model.hpp"

/**
 * @class UserService
 * @brief Provides high-level service operations for user management.
 *
 * This class defines static service methods that handle user-related
 * operations such as creating new users and authenticating existing ones.
 * It acts as a service layer between the application logic and the
 * underlying data-access layer.
 */
class UserService
{
public:
    /**
     * @brief Service to create a new user.
     *
     * This function encapsulates the logic required to create a new user account.
     */
    static void createUserService();

    /**
     * @brief Service to authenticate and log in a user.
     *
     * This function handles user login by verifying credentials and
     * returning the corresponding User object upon successful authentication.
     *
     * @return A User object representing the authenticated user.
     */
    static User loginUserService();
};
