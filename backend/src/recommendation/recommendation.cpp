//
// Created by zixin on 23-8-23.
//
// src/recommendation/recommendation.cpp
#include "recommendation.h"
#include "clustering.h"
#include <algorithm>

Recommendation::Recommendation(UserDB& user_db) : user_db_(user_db) {
}

std::vector<std::string> Recommendation::recommendFriends(const std::string& username) {
    // 获取所有用户的标签
    std::unordered_map<std::string, std::vector<std::string>> users = user_db_.getAllUserTags();

    // 执行聚类
    KMeans kmeans(5); // 例如分为5个聚类
    auto clusters = kmeans.run(users);

    // 找到与当前用户在同一聚类中的其他用户
    std::vector<std::string> recommendedFriends;
    for (const auto& cluster : clusters) {
        for (const auto& [user, _] : cluster) {
            if (user != username) {
                recommendedFriends.push_back(user);
            }
        }
    }

    // 排除已经是好友的用户
    std::sort(recommendedFriends.begin(), recommendedFriends.end());
    recommendedFriends.erase(std::unique(recommendedFriends.begin(), recommendedFriends.end()), recommendedFriends.end());

    return recommendedFriends; // 返回推荐的好友列表
}
