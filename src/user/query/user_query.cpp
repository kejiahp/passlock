#include <iostream>
#include <sstream>
#include <tuple>
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

bool UserQueries::deleteUserById(const int &userId)
{
    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();

        SQLite::Statement deleteCredStmt(db, "DELETE FROM credentials WHERE userId = ?;");
        deleteCredStmt.bind(1, userId);
        deleteCredStmt.exec();

        SQLite::Statement stmt(db, "DELETE FROM users WHERE id = ?;");
        stmt.bind(1, userId);
        stmt.exec();

        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ UserQueries::deleteUserById ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
}

bool UserQueries::updateUserDetails(const int &userId, const std::optional<std::string> &email,
                                    const std::optional<std::string> &type,
                                    const std::optional<std::string> &password)
{
    std::vector<std::tuple<std::string, int, std::string>> queryNbinders;
    int count = 1;
    if (email)
    {
        queryNbinders.push_back(std::make_tuple("email = ?", count, *email));
        ++count;
    }
    if (type)
    {
        queryNbinders.push_back(std::make_tuple("type = ?", count, *type));
        ++count;
    }
    if (password)
    {
        queryNbinders.push_back(std::make_tuple("password = ?", count, *password));
        ++count;
    }

    if (queryNbinders.size() <= 0)
    {
        return true;
    }

    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        std::ostringstream updateQuery;
        for (auto it = queryNbinders.begin(); it != queryNbinders.end(); ++it)
        {
            if (it != queryNbinders.begin())
            {
                updateQuery << ",";
            }
            updateQuery << std::get<0>(*it);
        }

        std::string query = "UPDATE users SET " + updateQuery.str() + " WHERE id = ?;";
        SQLite::Statement stmt(db, query);

        for (auto item : queryNbinders)
        {
            stmt.bind(std::get<1>(item), std::get<2>(item));
        }

        stmt.bind(count, userId);
        stmt.exec();
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ UserQueries::updateUserType ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
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

bool UserQueries::createAccount(const std::string &email, const std::string &password, const USER_TYPE &type, const std::string &key, const std::string &iv)
{
    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "INSERT INTO users (email, password, type, key, iv) VALUES(?, ?, ?, ?, ?);");
        stmt.bind(1, email);
        stmt.bind(2, password);
        stmt.bind(3, USER_TYPE_ToString(type));
        stmt.bind(4, key);
        stmt.bind(5, iv);
        stmt.exec();
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ UserQueries::createAccount ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
}
