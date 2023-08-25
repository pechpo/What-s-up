//
// Created by zixin on 23-8-23.
//

// src/database/user.cpp
#include "user.h"
#include <sqlite3.h>
#include <sstream>

UserDB::UserDB(DBConnection& connection)
        : connection_(connection.db) {
}

bool UserDB::addUser(const std::string& username, const std::string& password) {
    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool UserDB::validateUser(const std::string& username, const std::string& password) {
    std::string sql = "SELECT username FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool UserDB::updateUser(const std::string& username, const std::string& key, const std::string& value) {
    std::string sql = "UPDATE users SET " + key + " = ? WHERE username = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::unordered_map<std::string, std::vector<std::string>> UserDB::getAllUserTags() {
    std::unordered_map<std::string, std::vector<std::string>> userTags;
    std::string sql = "SELECT username, tags FROM users";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return userTags; // Return empty map on failure
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string tagsStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::vector<std::string> tags;
        std::istringstream iss(tagsStr);
        std::string tag;
        while (std::getline(iss, tag, ',')) {
            tags.push_back(tag);
        }
        userTags[username] = tags;
    }
    sqlite3_finalize(stmt);
    return userTags;
}