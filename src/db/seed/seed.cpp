/**
 * Here we will seed the database with the appropriate informations.
 */

#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>

#include "db.hpp"
#include "crypt/crypt.hpp"

namespace
{
    /**
     *@brief Private function: only accessible within this file to seed the database with an admin
     *   */
    void seedADMIN(const SQLite::Database &db, const std::string &seedEmail, const std::string &seedPassword)
    {
        try
        {
            std::string key = Crypt::generate128BitHex();
            std::string iv = Crypt::generate128BitHex();
            SQLite::Statement stmt(db, "INSERT OR IGNORE INTO users (email, password, type, key, iv) VALUES(?, ?, ?, ?, ?);");
            std::string passwordHash = Crypt::hashSHA256(seedPassword);
            stmt.bind(1, seedEmail);
            stmt.bind(2, passwordHash);
            stmt.bind(3, "ADMIN");
            stmt.bind(4, key);
            stmt.bind(5, iv);
            stmt.exec();
            std::cout << "🚀 Admin seed successful 🚀" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "🚫 Admin Seeding failed: " << e.what() << " 🚫" << std::endl;
        }
    }
}

namespace DB
{
    void seedDB()
    {
        std::string adminSeedEmail = "";    ///< Email is required to seed the database e.g. `admin@gmail.com`
        std::string adminSeedPassword = ""; ///< Password is required to seed the database e.g. `passLockAdmin12345@`

        if (adminSeedEmail.empty() || adminSeedPassword.empty())
        {
            std::cout << "🚫 Error thrown from file: ./src/db/seed/seed.cpp ;line 46 🚫" << std::endl;
            std::cout << "‼️ `adminSeedEmail` and `adminSeedPassword` required to seed the database ‼️" << std::endl;
            throw std::invalid_argument("`adminSeedEmail` and `adminSeedPassword` required to seed the database");
        }

        try
        {
            SQLite::Database db(DB::DATABASE_NAME, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

            std::string createUserTableQuery(
                "CREATE TABLE IF NOT EXISTS users"
                "("
                "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                "email TEXT UNIQUE NOT NULL,"
                "password TEXT NOT NULL,"
                "type TEXT CHECK(type IN (\"NORMAL\", \"ADMIN\")) NOT NULL DEFAULT \"NORMAL\","
                "key TEXT NOT NULL,"
                "iv TEXT NOT NULL,"
                "createdAt DATETIME DEFAULT CURRENT_TIMESTAMP,"
                "updatedAt DATETIME DEFAULT CURRENT_TIMESTAMP"
                ");");

            std::string userTableUpdatedAtTriggerQuery = R"(
        CREATE TRIGGER IF NOT EXISTS update_users_updatedAt
        AFTER UPDATE ON users
        FOR EACH ROW
        BEGIN
            UPDATE users
            SET updatedAt = CURRENT_TIMESTAMP
            WHERE id = OLD.id;
        END;
        )";

            std::string credentialsTableQuery(
                "CREATE TABLE IF NOT EXISTS credentials"
                "("
                "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                "userId INTEGER NOT NULL,"
                "title TEXT NOT NULL,"
                "email TEXT NULL,"
                "username TEXT NULL,"
                "password TEXT NULL,"
                "url TEXT NULL,"
                "createdAt DATETIME DEFAULT CURRENT_TIMESTAMP,"
                "updatedAt DATETIME DEFAULT CURRENT_TIMESTAMP,"
                "FOREIGN KEY (userId) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE"
                ");");

            std::string credentialsUpdatedAtTriggerQuery = R"(
        CREATE TRIGGER IF NOT EXISTS  update_credentails_updatedAt
        AFTER UPDATE ON credentials
        FOR EACH ROW
        BEGIN
            UPDATE credentials
            SET updatedAt = CURRENT_TIMESTAMP
            WHERE id = OLD.id;
        END;
        )";

            db.exec("PRAGMA foreign_keys = ON;");             // Enables foregin keys
            db.exec(createUserTableQuery);                    // Creates User table
            db.exec(userTableUpdatedAtTriggerQuery);          // Creates users.updatedAt trigger
            db.exec(credentialsTableQuery);                   // Create Credentials table
            db.exec(credentialsUpdatedAtTriggerQuery);        // Create credentails.updatedAt trigger
            seedADMIN(db, adminSeedEmail, adminSeedPassword); // Create admin if one does not exist.

            std::cout << "🚀 DB seed successfull" << " 🚀" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "🚫 Seeding failed: " << e.what() << " 🚫" << std::endl;
        }
    }
}
