//
// Created by zixin on 23-8-23.
//

// src/database/user.cpp
#include "user.h"
#include <sqlite3.h>
#include <sstream>

// 构造函数：连接到SQLite数据库
UserDB::UserDB(DBConnection& connection)
        : connection_(connection.db) {
}

// 创建用户
bool UserDB::addUser(const std::string& username, const std::string& password) {
    // SQL语句
    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        // 执行失败
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 获取用户信息
bool UserDB::validateUser(const std::string& username, const std::string& password) {
    // SQL语句
    std::string sql = "SELECT username FROM users WHERE username = ? AND password = ?";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // 执行成功
        sqlite3_finalize(stmt); // 清理
        return true;
    }
    // 执行失败
    sqlite3_finalize(stmt);
    return false;
}

// 更新用户信息
bool UserDB::updateUser(const std::string& username, const std::string& key, const std::string& value) {
    // SQL语句
    std::string sql = "UPDATE users SET " + key + " = ? WHERE username = ?";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        // 执行失败
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 获取所有用户的标签
std::unordered_map<std::string, std::vector<std::string>> UserDB::getAllUserTags() {
    std::unordered_map<std::string, std::vector<std::string>> userTags;
    std::string sql = "SELECT username, tags FROM users";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return userTags; // Return empty map on failure
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // 获取结果
        std::string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string tagsStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        // 解析标签
        std::vector<std::string> tags;
        // 使用逗号分隔符分割标签
        std::istringstream iss(tagsStr);
        // 逐个读取标签
        std::string tag;
        // 读取标签
        while (std::getline(iss, tag, ',')) {
            // 添加到标签列表
            tags.push_back(tag);
        }
        // 添加到结果集
        userTags[username] = tags;
    }
    // 清理
    sqlite3_finalize(stmt);
    // 返回结果
    return userTags;
}