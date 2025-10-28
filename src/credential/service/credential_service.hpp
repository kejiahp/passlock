#pragma once

#include "model/credential_model.hpp"
#include "model/user_model.hpp"

class CredentialService
{
public:
    static void createCredentialService(const User &user);
    static void viewUserCredentialService(const User &user);
    static void searchCredentialService(const User &user);
    static void updateCredentialService(const User &user);
    static void deleteCredentialService(const User &user);
};