#pragma once

#include <sstream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

/**
 * @enum USER_TYPE
 * @brief Represents the type of user in the system.
 *
 * This enumeration defines the different roles a user can have.
 */
enum class USER_TYPE
{
    NORMAL, ///< Standard user with limited privileges.
    ADMIN   ///< Standard user with limited privileges.
};

/**
 * @brief Converts a USER_TYPE enum value to its string representation.
 *
 * @param ut The USER_TYPE value to convert.
 * @return A C-style string representing the user type ("NORMAL" or "ADMIN").
 *
 * @note If an unknown USER_TYPE value is provided, the behavior is undefined.
 */
inline const char *USER_TYPE_ToString(USER_TYPE ut)
{
    switch (ut)
    {
    case USER_TYPE::NORMAL:
        return "NORMAL";
    case USER_TYPE::ADMIN:
        return "ADMIN";
    };
}

/**
 * @brief Converts a string to its corresponding USER_TYPE enum value.
 *
 * @param ut The string representation of the user type ("NORMAL" or "ADMIN").
 * @return The corresponding USER_TYPE value.
 *
 * @throws std::invalid_argument if the input string does not match a valid user type.
 */
inline USER_TYPE USER_TYPE_FromString(const std::string &ut)
{
    // wanted to use a switch but C++ switches apparently only take enums and integrals 😅😭
    if (ut == "NORMAL")
    {
        return USER_TYPE::NORMAL;
    }
    else if (ut == "ADMIN")
    {
        return USER_TYPE::ADMIN;
    }
    else
    {
        throw std::invalid_argument("Invalid USER_TYPE string");
    }
}

/**
 * @class User
 * @brief Class representation of the data stored in the `user` table it will serve as our Object-Relational Mapper.
 * */
class User
{
private:
    int id;
    std::string email;
    std::string password;
    USER_TYPE type;
    std::string key;
    std::string iv;
    std::string createdAt;
    std::string updatedAt;

public:
    User() = default;
    User(const int &id,
         const std::string &em,
         const std::string &pass,
         const std::string &ty,
         const std::string &ky,
         const std::string &iv,
         const std::string &crtAt,
         const std::string &uptAt) : id(id), email(em), password(pass), type(USER_TYPE_FromString(ty)), key(ky), iv(iv), createdAt(crtAt), updatedAt(uptAt)
    {
    }

    int getId() const { return id; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getIv() const { return iv; }
    std::string getKey() const { return key; }
    bool isAdmin() const { return type == USER_TYPE::ADMIN; }

    /**
     * Maps result for SQL query to a `User` object.
     *
     * @param stmt Represent a single resulting row from the SQL query.
     *
     * @returns `User` object
     */
    static User mapFromStatement(SQLite::Statement &stmt)
    {
        return User(
            stmt.getColumn("id").getInt(),
            stmt.getColumn("email").getText(),
            stmt.getColumn("password").getText(),
            stmt.getColumn("type").getText(),
            stmt.getColumn("key").getText(),
            stmt.getColumn("iv").getText(),
            stmt.getColumn("createdAt").getText(),
            stmt.getColumn("updatedAt").getText());
    }

    /**
     * Converts `User` to a string representation
     *
     * @return Stringified credential
     */
    std::string toString()
    {
        std::ostringstream output;
        output << "{" << "id: " << id << ", email: " << email << ", password: " << std::string(5, '*') << ", type: " << USER_TYPE_ToString(type) << ", key: " << std::string(5, '*') << ", iv: " << std::string(5, '*') << ", createdAt: " << createdAt << ", updatedAt: " << updatedAt << "}";
        return output.str();
    }
};
