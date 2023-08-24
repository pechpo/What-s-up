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
    Recommendation(UserDB& user_db);

    static const int MAX_RECOMMENDATIONS = 5; // 常量定义

    std::vector<std::string> recommendFriends(const std::string& username);

private:
    UserDB& user_db_; // 用户数据库引用
};

#endif //WHAT_S_UP_RECOMMENDATION_H
