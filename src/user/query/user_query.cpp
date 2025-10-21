#include <iostream>
#include "user_query.hpp"

std::vector<User> UserQueries::getAllUsers()
{
    std::vector<User> users;
    SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
    SQLite::Statement stmt(db, "SELECT * FROM users;");

    while (stmt.executeStep())
    {
        // `emplace_back` constructs the object in place, more performant than push_back
        users.emplace_back(User::mapFromStatement(stmt));
    }

    return users;
}

std::optional<User> UserQueries::getUserById(int userId)
{
    SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
    SQLite::Statement stmt(db, "SELECT * FROM users WHERE id = ?;");
    stmt.bind(1, userId);

    if (stmt.executeStep())
    {
        return User::mapFromStatement(stmt);
    }
    return std::nullopt;
}

std::optional<User> UserQueries::getUserByEmail(const std::string &email)
{
    SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
    SQLite::Statement stmt(db, "SELECT * FROM users WHERE email = ?;");
    stmt.bind(1, email);
    if (stmt.executeStep())
    {
        return User::mapFromStatement(stmt);
    }
    return std::nullopt;
}

bool UserQueries::createAccount(const std::string &email, const std::string &password, const USER_TYPE &type, const std::string &key)
{
    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "INSERT INTO users (email, password, type, key) VALUES(?, ?, ?, ?);");
        stmt.bind(1, email);
        stmt.bind(2, password);
        stmt.bind(3, USER_TYPE_ToString(type));
        stmt.bind(4, key);
        stmt.exec();
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ UserQueries::createAccount ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
}
