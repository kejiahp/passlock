#pragma once

#include "model/credential_model.hpp"
#include "model/user_model.hpp"

/**
 * @class CredentialService
 * @brief Provides high-level service operations for managing user credentials.
 *
 * This class defines static service methods that act as an interface
 * between the application logic and the underlying credential queries.
 * It supports creating, viewing, searching, updating, and deleting
 * credentials for a given user.
 */
class CredentialService
{
public:
    /**
     * @brief Service to create a new credential for the given user.
     * @param user The user for whom the credential will be created.
     */
    static void createCredentialService(const User &user);

    /**
     * @brief Service to display all credentials belonging to the given user.
     * @param user The user whose credentials will be retrieved and displayed.
     */
    static void viewUserCredentialService(const User &user);

    /**
     * @brief Service to search for credentials belonging to the given user.
     * @param user The user whose credentials will be searched.
     */
    static void searchCredentialService(const User &user);

    /**
     * @brief Service to update an existing credential for the given user.
     * @param user The user whose credential will be updated.
     */
    static void updateCredentialService(const User &user);

    /**
     * @brief Service to delete a credential belonging to the given user.
     * @param user The user whose credential will be deleted.
     */
    static void deleteCredentialService(const User &user);
};