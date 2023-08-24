//
// Created by zixin on 23-8-23.
//
// src/database/group.cpp
#include "group.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/exception/exception.hpp>

GroupDB::GroupDB(DBConnection& connection)
        : groups_(connection.getDatabase("WhatsUpDB").collection("groups")) {
}

bool GroupDB::createGroup(const std::string& groupId) {
    auto doc = bsoncxx::builder::stream::document{} << "groupId" << groupId << "members" << bsoncxx::builder::stream::open_array << bsoncxx::builder::stream::close_array << bsoncxx::builder::stream::finalize;
    try {
        groups_.insert_one(doc.view());
        return true;
    } catch (mongocxx::exception& e) {
        return false; // 插入失败
    }
}

bool GroupDB::addMember(const std::string& groupId, const std::string& memberId) {
    auto query = bsoncxx::builder::stream::document{} << "groupId" << groupId << bsoncxx::builder::stream::finalize;
    auto update = bsoncxx::builder::stream::document{} << "$push" << bsoncxx::builder::stream::open_document << "members" << memberId << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;
    try {
        groups_.update_one(query.view(), update.view());
        return true;
    } catch (mongocxx::exception& e) {
        return false; // 更新失败
    }
}

bool GroupDB::removeMember(const std::string& groupId, const std::string& memberId) {
    auto query = bsoncxx::builder::stream::document{} << "groupId" << groupId << bsoncxx::builder::stream::finalize;
    auto update = bsoncxx::builder::stream::document{} << "$pull" << bsoncxx::builder::stream::open_document << "members" << memberId << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;
    try {
        groups_.update_one(query.view(), update.view());
        return true;
    } catch (mongocxx::exception& e) {
        return false; // 更新失败
    }
}

std::vector<std::string> GroupDB::getMembers(const std::string& groupId) {
    auto query = bsoncxx::builder::stream::document{} << "groupId" << groupId << bsoncxx::builder::stream::finalize;
    auto result = groups_.find_one(query.view());
    std::vector<std::string> members;
    if (result) {
        for (const auto& member : result->view()["members"].get_array().value) {
            members.push_back(member.get_utf8().value.to_string());
        }
    }
    return members;
}
