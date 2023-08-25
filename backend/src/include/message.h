//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_MESSAGE_H
#define WHAT_S_UP_MESSAGE_H

#pragma once
#include "db_connection.h"
#include <string>
#include <vector>
#include <tuple>
#include <chrono>

struct Message {
    std::string sender;
    std::string receiver;
    std::string content;
    std::chrono::system_clock::time_point timestamp;
};

class MessageDB {
public:
    MessageDB(DBConnection& connection); // 构造函数，接收数据库连接

    // 保存新消息到数据库
    bool saveMessage(const std::string& groupId, const std::string& sender, const std::string& content);

    // 从数据库获取历史消息
    std::vector<std::tuple<std::string, std::string, std::string>> getMessages(const std::string& groupId);

private:
    sqlite3 *connection_; // 数据库连接引用
};

#endif //WHAT_S_UP_MESSAGE_H

