#pragma once

#include <string>
#include <optional>
#include <SQLiteCpp/SQLiteCpp.h>

class Credential
{
private:
    int id;
    int userId;
    std::string title;
    std::optional<std::string> email;
    std::optional<std::string> username;
    std::optional<std::string> password;
    std::optional<std::string> url;
    std::string createdAt;
    std::string updatedAt;

public:
    Credential() = default;
    Credential(
        const int &id,
        const int &userId,
        const std::string &title,
        const std::optional<std::string> &email,
        const std::optional<std::string> &username,
        const std::optional<std::string> &password,
        const std::optional<std::string> &url,
        const std::string &createdAt,
        const std::string &updatedAt) : id(id), userId(userId), title(title), email(email), username(username), password(password), url(url), createdAt(createdAt), updatedAt(updatedAt) {}

    int getId() const { return id; }
    int getUserId() const { return userId; }
    std::string getTitle() const { return title; }
    std::string getEmail() const
    {
        if (!email)
            return "";
        return *email;
    }
    std::string getUsername() const
    {
        if (!username)
            return "";
        return *username;
    }
    std::string getPassword() const
    {
        if (!password)
        {
            return "";
        }
        return *password;
    }
    std::string getUrl() const
    {
        if (!url)
        {
            return "";
        }
        return *url;
    }

    static Credential mapFromStatement(SQLite::Statement stmt)
    {
        return Credential(
            stmt.getColumn("id").getInt(),
            stmt.getColumn("userId").getInt(),
            stmt.getColumn("title").getString(),
            stmt.isColumnNull("email") ? std::nullopt : std::make_optional(stmt.getColumn("email").getString()),
            stmt.isColumnNull("username") ? std::nullopt : std::make_optional(stmt.getColumn("username").getString()),
            stmt.isColumnNull("password") ? std::nullopt : std::make_optional(stmt.getColumn("password").getString()),
            stmt.isColumnNull("url") ? std::nullopt : std::make_optional(stmt.getColumn("url").getString()),
            stmt.getColumn("createdAt").getText(),
            stmt.getColumn("updatedAt").getText());
    }
};