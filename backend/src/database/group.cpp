//
// Created by zixin on 23-8-23.
//
// src/database/group.cpp
#include "group.h"
#include <iostream>
#include <sqlite3.h>

// 构造函数：连接到SQLite数据库
GroupDB::GroupDB(DBConnection& connection)
        : connection_(connection.db) {
}

// 创建群组
bool GroupDB::createGroup(const std::string& groupId) {
    // SQL语句
    std::string sql = "INSERT INTO groups (groupId) VALUES (?)";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        std::cerr << "创建群组失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        // 执行失败
        std::cerr << "创建群组失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 添加成员到群组
bool GroupDB::addMember(const std::string& groupId, const std::string& memberId) {
    // SQL语句
    std::string sql = "INSERT INTO group_members (groupId, memberId) VALUES (?, ?)";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        std::cerr << "添加成员失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, memberId.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        // 执行失败
        std::cerr << "添加成员失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 从群组中删除成员
bool GroupDB::removeMember(const std::string& groupId, const std::string& memberId) {
    // SQL语句
    std::string sql = "DELETE FROM group_members WHERE groupId = ? AND memberId = ?";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        std::cerr << "删除成员失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, memberId.c_str(), -1, SQLITE_STATIC);
    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        // 执行失败
        std::cerr << "删除成员失败: " << sqlite3_errmsg(connection_) << std::endl;
        return false;
    }
    // 清理
    sqlite3_finalize(stmt);
    return true;
}

// 获取群组成员列表
std::vector<std::string> GroupDB::getMembers(const std::string& groupId) {
    // SQL语句
    std::string sql = "SELECT memberId FROM group_members WHERE groupId = ?";
    // SQLite语句对象
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // 准备失败
        std::cerr << "获取成员列表失败: " << sqlite3_errmsg(connection_) << std::endl;
        return {};
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, groupId.c_str(), -1, SQLITE_STATIC);
    // 查询结果
    std::vector<std::string> result;
    // 遍历结果
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // 获取成员ID
        std::string memberId = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        // 添加到结果中
        result.push_back(memberId);
    }
    // 清理
    sqlite3_finalize(stmt);
    // 返回结果
    return result;
}

//其他与SQLite数据库交互的方法将在此处实现