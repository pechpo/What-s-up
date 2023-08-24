//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_DB_CONNECTION_H
#define WHAT_S_UP_DB_CONNECTION_H
#pragma once
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

class DBConnection {
public:
    DBConnection();
    mongocxx::database getDatabase(const std::string& dbName);

private:
    mongocxx::instance instance_; // MongoDB实例
    mongocxx::client client_;     // MongoDB客户端
};

#endif //WHAT_S_UP_DB_CONNECTION_H
