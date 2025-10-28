#include <iostream>
#include <sstream>
#include <optional>

#include "db.hpp"
#include "crypt/crypt.hpp"
#include "credential_query.hpp"

bool CredentialQueries::createCredential(const int &userId,
                                         const std::string &title,
                                         const std::optional<std::string> &email,
                                         const std::optional<std::string> &username,
                                         const std::optional<std::string> &password,
                                         const std::optional<std::string> &url)
{
    try
    {

        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "INSERT INTO credentials (userId, title, email, username, password, url) VALUES (?, ?, ?, ?, ?, ?);");
        stmt.bind(1, userId);
        stmt.bind(2, title);
        if (email)
            stmt.bind(3, *email);
        else
            stmt.bind(3);

        if (username)
            stmt.bind(4, *username);
        else
            stmt.bind(4);

        if (password)
            stmt.bind(5, *password);
        else
            stmt.bind(5);

        if (url)
            stmt.bind(6, *url);
        else
            stmt.bind(6);

        stmt.exec();
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ CredentialQueries::createCredential ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
}

std::optional<Credential> CredentialQueries::getCredentialById(const std::string &credentialId, const std::string &userId)
{
    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "SELECT * FROM credentials WHERE id = ? AND userId = ? LIMIT 1;");
        stmt.bind(1, credentialId);
        stmt.bind(2, userId);
        if (stmt.executeStep())
        {
            return Credential::mapFromStatement(stmt);
        }
        return std::nullopt;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ CredentialQueries::getCredentialById ~ 🚫 =>" << e.what() << std::endl;
        return std::nullopt;
    }
}

std::vector<Credential> CredentialQueries::getCredentialsByUserId(const std::string &userId)
{
    try
    {
        std::vector<Credential> credentials;
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "SELECT * FROM credentials WHERE userId = ?;");
        stmt.bind(1, userId);
        while (stmt.executeStep())
        {
            credentials.emplace_back(Credential::mapFromStatement(stmt));
        }
        return credentials;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ CredentialQueries::getCredentialsByUserId ~ 🚫 =>" << e.what() << std::endl;
        return std::vector<Credential>();
    }
}

bool CredentialQueries::deleteCredentialById(const std::string &credentialId, const std::string &userId)
{
    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "DELETE FROM credentials WHERE id = ? AND userId = ?;");
        stmt.bind(1, credentialId);
        stmt.bind(2, userId);
        stmt.exec();
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ CredentialQueries::deleteCredentialById ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
}

bool CredentialQueries::updateCredential(
    const std::string &id,
    const std::string &userId,
    const std::optional<std::string> &title,
    const std::optional<std::string> &email,
    const std::optional<std::string> &username,
    const std::optional<std::string> &password,
    const std::optional<std::string> &url)
{
    try
    {
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        std::vector<std::string> updates;
        std::vector<std::pair<int, std::string>> binder;
        std::string query;
        int count = 1;

        if (title)
        {
            updates.push_back("title = ?");
            binder.emplace_back(std::make_pair(count, *title));
            ++count;
        }
        if (email)
        {
            updates.push_back("email = ?");
            binder.emplace_back(std::make_pair(count, *email));
            ++count;
        }
        if (username)
        {
            updates.push_back("username = ?");
            binder.emplace_back(std::make_pair(count, *username));
            ++count;
        }
        if (password)
        {
            updates.push_back("password = ?");
            binder.emplace_back(std::make_pair(count, *password));
            ++count;
        }
        if (url)
        {
            updates.push_back("url = ?");
            binder.emplace_back(std::make_pair(count, *url));
            ++count;
        }
        if (updates.size() <= 0)
        {
            return true;
        }
        std::ostringstream updateQuery;
        for (auto it = updates.begin(); it != updates.end(); ++it)
        {
            if (it != updates.begin())
            {
                updateQuery << ",";
            }
            updateQuery << *it;
        }
        query = "UPDATE credentials SET " + updateQuery.str() + " WHERE id = ? AND userId = ?;";
        std::cout << "Query: " << query << std::endl;

        SQLite::Statement stmt(db, query);
        for (auto bindVal : binder)
        {
            stmt.bind(bindVal.first, bindVal.second);
        }

        // Bind the credential ID to the query
        stmt.bind(count, id);
        ++count;
        stmt.bind(count, userId);

        std::cout << "SQL QUERY: " << stmt.getQuery() << std::endl;

        stmt.exec();
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ CredentialQueries::deleteCredentialById ~ 🚫 =>" << e.what() << std::endl;
        return false;
    }
}

std::vector<Credential> CredentialQueries::searchCredentialById(const std::string &userId, const std::string &searchVal)
{
    try
    {
        std::vector<Credential> searchResults;
        SQLite::Database &db = DB::DatabaseManager::getInstance().getDB();
        SQLite::Statement stmt(db, "SELECT * FROM credentials LIKE %?% WHERE userId = ? ORDER BY updatedAt DESC;");
        stmt.bind(1, searchVal);
        stmt.bind(2, userId);

        while (stmt.executeStep())
        {
            searchResults.emplace_back(Credential::mapFromStatement(stmt));
        }
        return searchResults;
    }
    catch (std::exception &e)
    {
        std::cerr << "🚫 SQLite execption ~ CredentialQueries::searchCredentialById ~ 🚫 =>" << e.what() << std::endl;
        return std::vector<Credential>();
    }
}