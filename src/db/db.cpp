#include <string>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
// #include <utilities>

void bae()
{
    try
    {
        // Open or create the database
        SQLite::Database db("example.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Create a table
        db.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT);");

        // Insert a row
        db.exec("INSERT INTO users (name) VALUES ('Alice');");

        // Query data
        SQLite::Statement query(db, "SELECT id, name FROM users;");
        while (query.executeStep())
        {
            int id = query.getColumn(0);
            std::string name = query.getColumn(1);
            std::cout << id << ": " << name << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}