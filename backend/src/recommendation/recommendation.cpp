//
// Created by zixin on 23-8-23.
//

// src/recommendation/recommendation.cpp

#include "recommendation.h"
#include "clustering.h"
#include "db.h"
#include <unordered_map>
#include <vector>
#include <QSqlQuery>

Recommendation::Recommendation() {

}

Recommendation *Recommendation::rd = nullptr;

Recommendation *Recommendation::get_instance() {
    if (rd == nullptr) {
        rd = new Recommendation();
    }
    return rd;
}

std::vector<quint32> Recommendation::getFriends(const quint32 &userId) {
    DB *db = DB::get_instance();
    return db->getFriends(userId);
}

std::vector<quint32> Recommendation::recommendFriends(const quint32 &userId) {
    DB *db = DB::get_instance();

    std::unordered_map<quint32, std::vector<int>> users = db->get_all_tags();
    // Fetch user tags from the database

    KMeans kmeans(4);  // Assuming 4 clusters
    auto clusters = kmeans.run(users);

    // Logic to recommend friends based on clustering result
    std::vector<quint32> recommended_friends;
    std::vector<quint32> existing_friends = getFriends(userId);  // Fetch existing friends to exclude them

    for (const auto &cluster: clusters) {
        for (const auto &[uid, _]: cluster) {
            if (uid == userId) {
                for (const auto &[other_uid, _]: cluster) {
                    if (other_uid != userId && std::find(existing_friends.begin(), existing_friends.end(), other_uid) ==
                                               existing_friends.end()) {
                        recommended_friends.push_back(other_uid);
                    }
                }
                break;
            }
        }
    }

    return recommended_friends;
}