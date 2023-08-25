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
    UserDB(DBConnection& connection); // 构造函数，接收数据库连接

    // 添加新用户到数据库
    bool addUser(const std::string& username, const std::string& password);

    // 验证数据库中的用户凭证
    bool validateUser(const std::string& username, const std::string& password);

    // 在数据库中更新用户信息
    bool updateUser(const std::string& username, const std::string& key, const std::string& value);

    // 从数据库获取所有用户的标签（例如兴趣或爱好）
    std::unordered_map<std::string, std::vector<std::string>> getAllUserTags();

private:
    sqlite3 *connection_; // 数据库连接引用
};

#endif //WHAT_S_UP_USER_H

