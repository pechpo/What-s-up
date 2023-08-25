//
// Created by zixin on 23-8-23.
//
// src/database/db_connection.cpp
#include "db_connection.h"
#include <iostream>

// 构造函数：连接到SQLite数据库
DBConnection::DBConnection(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
}

// 析构函数：关闭数据库连接
DBConnection::~DBConnection() {
    sqlite3_close(db);
}

// 其他与SQLite数据库交互的方法将在此处实现


