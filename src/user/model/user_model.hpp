#pragma once

#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

enum class USER_TYPE
{
    NORMAL,
    ADMIN
};

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
    User(int id,
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
};