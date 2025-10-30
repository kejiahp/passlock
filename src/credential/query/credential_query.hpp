#pragma once

#include <vector>
#include <optional>

#include "model/credential_model.hpp"

/**
 * @class CredentialQueries
 * @brief Provides static methods to query, create, update, and delete user credentials.
 *
 * This class acts as a data-access layer for credential management.
 * It supports operations such as retrieving credentials by user ID,
 * searching, creating, updating, and deleting credentials.
 */
class CredentialQueries
{
public:
    /**
     * @brief Retrieve all credentials in the system.
     *
     * This function should only be used by administrators, as it exposes
     * all credential records.
     */
    static std::vector<Credential> getAllCredentials();

    /**
     * @brief Retrieve all credentials associated with a given user.
     * @param userId The unique identifier of the user.
     * @return A vector of Credential objects belonging to the user.
     */
    static std::vector<Credential> getCredentialsByUserId(const int &userId);

    /**
     * @brief Retrieve a specific credential by its ID for a given user.
     * @param credentialId The unique identifier of the credential.
     * @param userId The unique identifier of the user who owns the credential.
     * @return An optional Credential object. Contains a value if found, otherwise empty.
     */
    static std::optional<Credential> getCredentialById(const int &credentialId, const int &userId);

    /**
     * @brief Search for credentials by a partial or full credential ID string.
     * @param userId The unique identifier of the user.
     * @param searchVal The search string to match against credential IDs.
     * @return A vector of Credential objects matching the search criteria.
     */
    static std::vector<Credential> searchCredentialById(const int &userId, const std::string &searchVal);

    /**
     * @brief Delete a credential by its ID for a given user.
     * @param credentialId The unique identifier of the credential to delete.
     * @param userId The unique identifier of the user who owns the credential.
     * @return True if the credential was successfully deleted, false otherwise.
     */
    static bool deleteCredentialById(const int &credentialId, const int &userId);

    /**
     * @brief Create a new credential for a given user.
     * @param userId The unique identifier of the user.
     * @param title The title or label for the credential.
     * @param email Optional email associated with the credential.
     * @param username Optional username associated with the credential.
     * @param password Optional password associated with the credential.
     * @param url Optional URL associated with the credential.
     * @return True if the credential was successfully created, false otherwise.
     */
    static bool createCredential(
        const int &userId,
        const std::string &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url);

    /**
     * @brief Update an existing credential for a given user.
     * @param id The unique identifier of the credential to update.
     * @param userId The unique identifier of the user who owns the credential.
     * @param title Optional new title for the credential.
     * @param email Optional new email for the credential.
     * @param username Optional new username for the credential.
     * @param password Optional new password for the credential.
     * @param url Optional new URL for the credential.
     * @return True if the credential was successfully updated, false otherwise.
     */
    static bool updateCredential(
        const int &id,
        const int &userId,
        const std::optional<std::string> &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url);
};