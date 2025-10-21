/**
 * Here we will seed the database with the appropriate informations.
 */

#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include "db.hpp"

// Seeds the database:
// - creates the `users` table.
// - creates the `credentials table.`
// - creates the `updatedAt` trigger for the `users` table.
// - creates the `updatedAt` trigger for the `credentials` table.
namespace DB
{
    void seedDB()
    {
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

            db.exec("PRAGMA foreign_keys = ON;");      // Enables foregin keys
            db.exec(createUserTableQuery);             // Creates User table
            db.exec(userTableUpdatedAtTriggerQuery);   // Creates users.updatedAt trigger
            db.exec(credentialsTableQuery);            // Create Credentials table
            db.exec(credentialsUpdatedAtTriggerQuery); // Create credentails.updatedAt trigger

            std::cout << "🚀 DB seed successfull" << " 🚀" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "🚫 Seeding failed: " << e.what() << " 🚫" << std::endl;
        }
    }
}
