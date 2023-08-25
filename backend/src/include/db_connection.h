//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_DB_CONNECTION_H
#define WHAT_S_UP_DB_CONNECTION_H
#pragma once
#include <sqlite3.h>
#include <string>

class DBConnection {
public:
    DBConnection(const std::string& dbPath);
    ~DBConnection();


    sqlite3* db;
    // SQLite数据库实例
};

#endif //WHAT_S_UP_DB_CONNECTION_H
