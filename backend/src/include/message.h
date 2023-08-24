//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_MESSAGE_H
#define WHAT_S_UP_MESSAGE_H
#pragma once
#include "db_connection.h"
#include <string>
#include <vector>

class MessageDB {
public:
    MessageDB(DBConnection& connection);

    // 保存新消息
    bool saveMessage(const std::string& groupId, const std::string& sender, const std::string& content);

    // 获取历史消息
    std::vector<std::tuple<std::string, std::string, std::string>> getMessages(const std::string& groupId);

private:
    mongocxx::collection messages_; // 消息集合
};

#endif //WHAT_S_UP_MESSAGE_H
