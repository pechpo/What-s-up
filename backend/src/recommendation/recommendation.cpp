//
// Created by zixin on 23-8-23.
//

// src/recommendation/recommendation.cpp

#include "recommendation.h"
#include "clustering.h"
#include <unordered_map>
#include <vector>

Recommendation::Recommendation() {

}

std::vector<quint32> Recommendation::recommendFriends(const quint32& userId) {
    std::unordered_map<quint32, std::vector<int>> users;  // Replace with actual data
    KMeans kmeans(5);  // Assuming 5 clusters
    auto clusters = kmeans.run(users);

    // Logic to recommend friends based on clustering result
    std::vector<quint32> recommended_friends;
    for (const auto& cluster : clusters) {
        for (const auto& [uid, _] : cluster) {
            if (uid == userId) {
                for (const auto& [other_uid, _] : cluster) {
                    if (other_uid != userId) {
                        recommended_friends.push_back(other_uid);
                    }
                }
                break;
            }
        }
    }

    return recommended_friends;
}

std::vector<quint32> Recommendation::recommendGroups(const quint32& userId) {
    std::unordered_map<quint32, std::vector<int>> groups;  // Replace with actual data
    KMeans kmeans(5);  // Assuming 5 clusters
    auto clusters = kmeans.run(groups);

    // Logic to recommend groups based on clustering result
    std::vector<quint32> recommended_groups;
    for (const auto& cluster : clusters) {
        for (const auto& [gid, _] : cluster) {
            recommended_groups.push_back(gid);
        }
    }

    return recommended_groups;
}

std::vector<quint32> Recommendation::getFriends(const quint32& userId) {
    // Fetch the friend list of the user from the database (placeholder logic)
    return {1, 2, 3};  // Example friend IDs
}

std::vector<quint32> Recommendation::getGroups(const quint32& userId) {
    // Fetch the group list of the user from the database (placeholder logic)
    return {101, 102, 103};  // Example group IDs
}

std::vector<int> Recommendation::getTags(const quint32& userId) {
    // Fetch the tags of the user from the database (placeholder logic)
    return {0, 1, 0, 1};  // Example tags
}

std::vector<int> Recommendation::getFriendsTags(const quint32& userId) {
    // Fetch the tags of the friends of the user from the database (placeholder logic)
    return {1, 0, 1, 0};  // Example tags
}

std::vector<int> Recommendation::getGroupsTags(const quint32& userId) {
    // Fetch the tags of the groups of the user from the database (placeholder logic)
    return {1, 1, 0, 0};  // Example tags
}
