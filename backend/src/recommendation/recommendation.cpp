//
// Created by zixin on 23-8-23.
//
// src/recommendation/recommendation.cpp

#include "recommendation.h"
#include "clustering.h"

Recommendation::Recommendation() = default;

std::vector<std::string> Recommendation::getFriends(const std::string& username) {
    // Your database query code here
    return std::vector<std::string>{"friend1", "friend2"}; // Just for demonstration
}

std::vector<std::string> Recommendation::getGroups(const std::string& username) {
    // Your database query code here
    return std::vector<std::string>{"group1", "group2"}; // Just for demonstration
}

std::vector<std::string> Recommendation::getTags(const std::string& username) {
    // Your database query code here
    return std::vector<std::string>{"tag1", "tag2"}; // Just for demonstration
}

std::vector<std::string> Recommendation::getFriendsTags(const std::string& username) {
    // Your database query code here
    return std::vector<std::string>{"friendTag1", "friendTag2"}; // Just for demonstration
}

std::vector<std::string> Recommendation::getGroupsTags(const std::string& username) {
    // Your database query code here
    return std::vector<std::string>{"groupTag1", "groupTag2"}; // Just for demonstration
}

// ... (Your existing recommendFriends and recommendGroups functions here)

std::vector<std::string> Recommendation::recommendFriends(const std::string& username) {
    // 从数据库中获取用户的好友列表
    auto friends = getFriends(username);
    // 从数据库中获取用户的好友的标签
    auto friendsTags = getFriendsTags(username);
    // 从数据库中获取用户的标签
    auto tags = getTags(username);
    // 将用户的标签和好友的标签合并
    tags.insert(tags.end(), friendsTags.begin(), friendsTags.end());
    // 去除重复的标签
    std::sort(tags.begin(), tags.end());
    tags.erase(std::unique(tags.begin(), tags.end()), tags.end());
    // 将用户的标签和好友的标签转换为特征向量
    std::unordered_map<std::string, std::vector<std::string>> users;
    users[username] = tags;
    for (const auto& friendName : friends) {
        users[friendName] = getTags(friendName);
    }
    KMeans kmeans(3);
    auto clusters = kmeans.run(users);
    // 选择最大的聚类
    std::vector<std::pair<std::string, std::vector<double>>> largestCluster;
    for (const auto& cluster : clusters) {
        if (cluster.size() > largestCluster.size()) {
            largestCluster = cluster;
        }
    }
    // 从聚类中选择好友
    std::vector<std::string> recommendedFriends;
    for (const auto& [friendName, tags] : largestCluster) {
        recommendedFriends.push_back(friendName);
    }
    return recommendedFriends;
}

std::vector<std::string> Recommendation::recommendGroups(const std::string& username) {
    // 从数据库中获取用户的群组列表
    auto groups = getGroups(username);
    // 从数据库中获取用户的群组的标签
    auto groupsTags = getGroupsTags(username);
    // 从数据库中获取用户的标签
    auto tags = getTags(username);
    // 将用户的标签和群组的标签合并
    tags.insert(tags.end(), groupsTags.begin(), groupsTags.end());
    // 去除重复的标签
    std::sort(tags.begin(), tags.end());
    tags.erase(std::unique(tags.begin(), tags.end()), tags.end());
    // 将用户的标签和群组的标签转换为特征向量
    std::unordered_map<std::string, std::vector<std::string>> users;
    users[username] = tags;
    for (const auto& group : groups) {
        users[group] = getTags(group);
    }
    KMeans kmeans(3);
    auto clusters = kmeans.run(users);
    // 选择最大的聚类
    std::vector<std::pair<std::string, std::vector<double>>> largestCluster;
    for (const auto& cluster : clusters) {
        if (cluster.size() > largestCluster.size()) {
            largestCluster = cluster;
        }
    }
    // 从聚类中选择群组
    std::vector<std::string> recommendedGroups;
    for (const auto& [group, tags] : largestCluster) {
        recommendedGroups.push_back(group);
    }
    return recommendedGroups;
}
