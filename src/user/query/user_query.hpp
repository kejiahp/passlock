#pragma once

#include <vector>
#include <optional>
#include "db.hpp"
#include "model/user_model.hpp"

class UserQueries
{
public:
    static std::vector<User> getAllUsers();
    static std::optional<User> getUserById(int userId);
    static std::optional<User> getUserByEmail(const std::string &email);
    static bool createAccount(const std::string &email, const std::string &password, const USER_TYPE &type, const std::string &key, const std::string &iv);
};