#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>

/**
 * @namespace DB
 * @brief Contains database-related constants, functions, and classes for managing the application database.
 */
namespace DB
{

    constexpr const char *DATABASE_NAME = "passlockDBlite.db";

    /**
     * @brief Seeds the database with initial data.
     *
     * creates the `users` table.
     *
     * creates the `credentials` table.
     *
     * creates the `updatedAt` trigger for the `users` table.
     *
     * creates the `updatedAt` trigger for the `credentials` table.
     */
    void seedDB();

    /**
     * @class DatabaseManager
     * @brief Singleton class responsible for managing the database connection.
     *
     * Ensures that only one active connection to the SQLite database exists
     * throughout the lifetime of the program. Provides access to the underlying
     * SQLite::Database instance.
     */
    class DatabaseManager
    {
    public:
        /**
         * @brief Retrieves the singleton instance of the DatabaseManager.
         *
         * If the instance does not exist, it will be created with the provided
         * database path. Subsequent calls will return the same instance.
         *
         * @param dbPath Path to the SQLite database file. Defaults to DB::DATABASE_NAME.
         * @return Reference to the singleton DatabaseManager instance.
         */
        static DatabaseManager &getInstance(const std::string &dbPath = DATABASE_NAME)
        {
            static DatabaseManager instance(dbPath); // static inside a function => instance is created only once, the first time the function is called. It persists for the lifetime of the program.
            return instance;
        }

        /**
         * @brief Provides access to the underlying SQLite database object.
         * @return Reference to the SQLite::Database instance.
         */
        SQLite::Database &getDB()
        {
            return *db;
        }

    private:
        std::unique_ptr<SQLite::Database> db; ///< Smart pointer managing the SQLite database connection.

        /**
         * @brief Constructs a DatabaseManager with the given database path.
         * @param dbPath Path to the SQLite database file.
         *
         * Opens the database in read/write mode, creating it if it does not exist.
         */
        DatabaseManager(const std::string &dbPath)
        {
            db = std::make_unique<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        }

        /**
         * @brief Default destructor.
         *
         * Automatically cleans up resources. Equivalent to compiler-generated destructor.
         */
        ~DatabaseManager() = default; // the compile will generate the default destructor, equivalent to writing this ~DatabaseManager(){}

        DatabaseManager(const DatabaseManager &) = delete;            ///< Deleted copy constructor to enforce singleton pattern.
        DatabaseManager &operator=(const DatabaseManager &) = delete; ///< Deleted assignment operator to enforce singleton pattern.
    };
}