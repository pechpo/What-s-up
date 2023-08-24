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
    GroupDB(DBConnection& connection);

    // 创建新群组
    bool createGroup(const std::string& groupId);

    // 添加群组成员
    bool addMember(const std::string& groupId, const std::string& memberId);

    // 删除群组成员
    bool removeMember(const std::string& groupId, const std::string& memberId);

    // 获取群组成员列表
    std::vector<std::string> getMembers(const std::string& groupId);

private:
    mongocxx::collection groups_; // 群组集合
};

#endif //WHAT_S_UP_GROUP_H
