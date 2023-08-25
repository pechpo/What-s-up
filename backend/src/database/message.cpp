//
// Created by zixin on 23-8-23.
//
// src/database/message.cpp
#include "message.h"
#include <sqlite3.h>
#include <tuple>

MessageDB::MessageDB(DBConnection& connection)
        : connection_(connection.db) { // 使用SQLite连接
}

// 保存消息到数据库
bool MessageDB::saveMessage(const std::string& groupId, const std::string& sender, const std::string& content) {
    // SQL语句
    std::string sql = "INSERT INTO messages (groupId, sender, content) VALUES (?, ?, ?)";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false; // 准备失败
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, sender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, content.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        // 执行失败
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 获取群组的所有消息
std::vector<std::tuple<std::string, std::string, std::string>> MessageDB::getMessages(const std::string& groupId) {
    std::string sql = "SELECT sender, content FROM messages WHERE groupId = ?";
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return {}; // 准备失败
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    // 查询结果
    std::vector<std::tuple<std::string, std::string, std::string>> result;
    // 遍历结果
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // 获取结果
        std::string sender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string content = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        // 添加到结果集
        result.emplace_back(groupId, sender, content);
    }
    // 清理
    sqlite3_finalize(stmt);
    return result;
}
