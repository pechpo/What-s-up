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

//动漫、漫画、游戏、旅游、音乐、阅读、写作、摄影、美食、哲学、健身、美妆、单身、已婚、学生、职场新人、中年、退休、猫奴、犬奴、（16种mbti）

// Define tag indices for better readability
const int ANIME = 0;
const int MANGA = 1;
const int GAMING = 2;
const int TRAVEL = 3;
const int MUSIC = 4;
const int READING = 5;
const int WRITING = 6;
const int PHOTOGRAPHY = 7;
const int FOOD = 8;
const int PHILOSOPHY = 9;
const int FITNESS = 10;
const int BEAUTY = 11;
const int SINGLE = 12;
const int MARRIED = 13;
const int STUDENT = 14;
const int NEWCOMER = 15;
const int MIDDLE_AGE = 16;
const int RETIRED = 17;
const int CAT = 18;
const int DOG = 19;
const int ENTJ = 20;
const int ENTP = 21;
const int ENFJ = 22;
const int ENFP = 23;
const int ESFJ = 24;
const int ESFP = 25;
const int ESTJ = 26;
const int ESTP = 27;
const int INTJ = 28;
const int INTP = 29;
const int INFJ = 30;
const int INFP = 31;
const int ISFJ = 32;
const int ISFP = 33;
const int ISTJ = 34;
const int ISTP = 35;


Recommendation::Recommendation() {

}

std::vector<quint32> Recommendation::getFriends(const quint32& userId) {
    DB *db = DB::get_instance();
    return db->getFriends(userId);
}

std::vector<quint32> Recommendation::recommendFriends(const quint32& userId) {
    DB *db = DB::get_instance();

    std::unordered_map<quint32, std::vector<int>> users = db->get_all_tags();
    // Fetch user tags from the database

    KMeans kmeans(5);  // Assuming 5 clusters
    auto clusters = kmeans.run(users);

    // Logic to recommend friends based on clustering result
    std::vector<quint32> recommended_friends;
    std::vector<quint32> existing_friends = getFriends(userId);  // Fetch existing friends to exclude them

    for (const auto& cluster : clusters) {
        for (const auto& [uid, _] : cluster) {
            if (uid == userId) {
                for (const auto& [other_uid, _] : cluster) {
                    if (other_uid != userId && std::find(existing_friends.begin(), existing_friends.end(), other_uid) == existing_friends.end()) {
                        recommended_friends.push_back(other_uid);
                    }
                }
                break;
            }
        }
    }

    return recommended_friends;
}