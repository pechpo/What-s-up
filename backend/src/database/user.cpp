//
// Created by zixin on 23-8-23.
//

// src/database/user.cpp
#include "user.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/exception/exception.hpp>
#include <iostream>
#include <optional>

UserDB::UserDB(DBConnection& connection)
        : users_(connection.getDatabase("WhatsUpDB").collection("users")) {
}

bool UserDB::addUser(const std::string& username, const std::string& password) {
    auto doc = bsoncxx::builder::stream::document{} << "username" << username << "password" << password << bsoncxx::builder::stream::finalize;
    try {
        users_.insert_one(doc.view());
        return true;
    } catch (mongocxx::exception& e) {
        return false; // 插入失败
    }
}

bool UserDB::validateUser(const std::string& username, const std::string& password) {
    auto query = bsoncxx::builder::stream::document{} << "username" << username << "password" << password << bsoncxx::builder::stream::finalize;
    auto result = users_.find_one(query.view());
    return result.has_value(); // 检查结果是否包含值
}

bool UserDB::updateUser(const std::string& username, const std::string& key, const std::string& value) {
    auto query = bsoncxx::builder::stream::document{} << "username" << username << bsoncxx::builder::stream::finalize;
    auto update = bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << key << value << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;
    try {
        users_.update_one(query.view(), update.view());
        return true;
    } catch (mongocxx::exception& e) {
        return false; // 更新失败
    }
}

std::unordered_map<std::string, std::vector<std::string>> UserDB::getAllUserTags() {
    std::unordered_map<std::string, std::vector<std::string>> userTags;
    try {
        auto cursor = users_.find({});
        for (auto&& doc : cursor) {
            std::string username = doc["username"].get_utf8().value.to_string();
            std::vector<std::string> tags;
            if (doc["tags"]) { // 确保“tags”字段存在
                auto tagsArray = doc["tags"].get_array().value;
                for (const auto& tag : tagsArray) {
                    tags.push_back(tag.get_utf8().value.to_string());
                }
                userTags[username] = tags;
            }
        }
    } catch (mongocxx::exception& e) {
        std::cerr << "Error fetching user tags: " << e.what() << '\n'; // 打印异常信息
    }
    return userTags;
}
