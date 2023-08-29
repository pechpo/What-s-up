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

private:
    // Fetch the friend list of the user from the database
    std::vector<quint32> getFriends(const quint32& userId);

    // Fetch the tags of the user from the database
    std::vector<int> getTags(const quint32& userId);
};

#endif //WHAT_S_UP_RECOMMENDATION_H
