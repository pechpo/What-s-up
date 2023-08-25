//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_USER_H
#define WHAT_S_UP_USER_H

#pragma once
#include "db_connection.h"
#include <string>
#include <unordered_map>
#include <vector>

class UserDB {
public:
    UserDB(DBConnection& connection);

    // 添加新用户
    bool addUser(const std::string& username, const std::string& password);

    // 验证用户凭证
    bool validateUser(const std::string& username, const std::string& password);

    // 更新用户信息
    bool updateUser(const std::string& username, const std::string& key, const std::string& value);

    // 获取所有用户的标签（例如兴趣或爱好）
    std::unordered_map<std::string, std::vector<std::string>> getAllUserTags();

private:
    mongocxx::collection users_; // 用户集合
};

#endif //WHAT_S_UP_USER_H
