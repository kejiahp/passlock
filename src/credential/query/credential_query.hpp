#pragma once

#include <vector>
#include <optional>

#include "model/credential_model.hpp"

class CredentialQueries
{
public:
    static std::vector<Credential> getCredentialsByUserId(const int &userId);
    static std::optional<Credential> getCredentialById(const int &credentialId, const int &userId);
    static std::vector<Credential> searchCredentialById(const int &userId, const std::string &searchVal);
    static bool deleteCredentialById(const int &credentialId, const int &userId);
    static bool createCredential(
        const int &userId,
        const std::string &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url);
    static bool updateCredential(
        const int &id,
        const int &userId,
        const std::optional<std::string> &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url);
};