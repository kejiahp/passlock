#pragma once

#include <vector>
#include <optional>

#include "model/credential_model.hpp"

class CredentialQueries
{
    static std::vector<Credential> getCredentialsByUserId(const std::string &userId);
    static std::optional<Credential> getCredentialById(const std::string &credentialId, const std::string &userId);
    static std::vector<Credential> searchCredentialById(const std::string &userId, const std::string &searchVal);
    static bool deleteCredentialById(const std::string &credentialId, const std::string &userId);
    static bool createCredential(
        const int &userId,
        const std::string &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url);
    static bool updateCredential(
        const std::string &id,
        const std::string &userId,
        const std::optional<std::string> &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url);
};