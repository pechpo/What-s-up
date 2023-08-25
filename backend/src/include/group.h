//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_GROUP_H
#define WHAT_S_UP_GROUP_H
#pragma once
#include "db_connection.h"
#include <string>
#include <vector>

class GroupDB {
public:
    GroupDB(DBConnection& connection); // 构造函数，接收数据库连接

    // 在数据库中创建新群组
    bool createGroup(const std::string& groupId);

    // 在数据库中添加群组成员
    bool addMember(const std::string& groupId, const std::string& memberId);

    // 在数据库中删除群组成员
    bool removeMember(const std::string& groupId, const std::string& memberId);

    // 从数据库中获取群组成员列表
    std::vector<std::string> getMembers(const std::string& groupId);

private:
    sqlite3 *connection_; // 数据库连接引用
};

#endif //WHAT_S_UP_GROUP_H

