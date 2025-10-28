#pragma once

#include "model/credential_model.hpp"
#include "model/user_model.hpp"

class CredentialService
{
public:
    static void createCredentialService(const User &user);
};