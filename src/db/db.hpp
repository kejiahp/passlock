#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>

namespace DB
{

    constexpr const char *DATABASE_NAME = "passlockDBlite.db";

    void seedDB();

    // DataManager Singleton
    // Ensuring only one database connection is active
    class DatabaseManager
    {
    public:
        static DatabaseManager &getInstance(const std::string &dbPath = DATABASE_NAME)
        {
            static DatabaseManager instance(dbPath); // static inside a function => instance is created only once, the first time the function is called. It persists for the lifetime of the program.
            return instance;
        }

        SQLite::Database &getDB()
        {
            return *db;
        }

    private:
        std::unique_ptr<SQLite::Database> db;

        DatabaseManager(const std::string &dbPath)
        {
            db = std::make_unique<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        }

        ~DatabaseManager() = default; // the compile will generate the default destructor, equivalent to writing this ~DatabaseManager(){}

        DatabaseManager(const DatabaseManager &) = delete;            // delete copy constructor
        DatabaseManager &operator=(const DatabaseManager &) = delete; // delete the copy assignment operator
    };
}