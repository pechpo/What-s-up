//
// Created by zixin on 23-8-23.
//
// src/database/group.cpp
#include "group.h"
#include <iostream>
#include <sqlite3.h>

GroupDB::GroupDB(DBConnection& connection)
        : connection_(connection.db) {
}

// 创建群组
bool GroupDB::createGroup(const std::string& groupId) {
    std::string sql = "INSERT INTO groups (groupId) VALUES (?)";
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "创建群组失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "创建群组失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 添加成员到群组
bool GroupDB::addMember(const std::string& groupId, const std::string& memberId) {
    std::string sql = "INSERT INTO group_members (groupId, memberId) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "添加成员失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, memberId.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "添加成员失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 其他与SQLite数据库交互的方法将在此处实现
