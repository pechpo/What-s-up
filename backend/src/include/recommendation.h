//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_RECOMMENDATION_H
#define WHAT_S_UP_RECOMMENDATION_H
#pragma once

#include <string>
#include <vector>
#include "user.h"

class Recommendation {
public:
    Recommendation();

    // 为用户推荐好友
    std::vector<std::string> recommendFriends(const std::string& username);

    // 为用户推荐群组
    std::vector<std::string> recommendGroups(const std::string& username);

    // 为用户推荐活动
    std::vector<std::string> recommendActivities(const std::string& username);

    // 其他可能的成员函数声明

private:
    // 从数据库中获取用户的好友列表
    std::vector<std::string> getFriends(const std::string& username);

    // 从数据库中获取用户的群组列表
    std::vector<std::string> getGroups(const std::string& username);

    // 从数据库中获取用户的标签
    std::vector<std::string> getTags(const std::string& username);

    // 从数据库中获取用户的好友的标签
    std::vector<std::string> getFriendsTags(const std::string& username);

    // 从数据库中获取用户的群组的标签
    std::vector<std::string> getGroupsTags(const std::string& username);
};

#endif //WHAT_S_UP_RECOMMENDATION_H
