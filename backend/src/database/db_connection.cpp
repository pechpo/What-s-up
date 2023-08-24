//
// Created by zixin on 23-8-23.
//
// src/database/db_connection.cpp
#include "db_connection.h"
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>

// 连接到MongoDB数据库

DBConnection::DBConnection()
        : client_{mongocxx::uri{"mongodb+srv://What-s-up:q_e323wJBMrw4_G@cluster0.o7fxkly.mongodb.net/?retryWrites=true&w=majority"}} {
}

mongocxx::database DBConnection::getDatabase(const std::string& dbName) {
    return client_.database(dbName);
}

