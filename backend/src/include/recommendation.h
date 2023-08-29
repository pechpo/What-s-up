//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_RECOMMENDATION_H
#define WHAT_S_UP_RECOMMENDATION_H
#pragma once
#include <vector>
#include <string>
#include "user.h"

class Recommendation {
public:
    Recommendation();

    // Recommend friends for the user
    std::vector<quint32> recommendFriends(const quint32& userId);

    // Recommend groups for the user
    std::vector<quint32> recommendGroups(const quint32& userId);

    // Recommend activities for the user (if needed)
    std::vector<std::string> recommendActivities(const quint32& userId);

private:
    // Fetch the friend list of the user from the database
    std::vector<quint32> getFriends(const quint32& userId);

    // Fetch the group list of the user from the database
    std::vector<quint32> getGroups(const quint32& userId);

    // Fetch the tags of the user from the database
    std::vector<int> getTags(const quint32& userId);

    // Fetch the tags of the friends of the user from the database
    std::vector<int> getFriendsTags(const quint32& userId);

    // Fetch the tags of the groups of the user from the database
    std::vector<int> getGroupsTags(const quint32& userId);
};

#endif //WHAT_S_UP_RECOMMENDATION_H
