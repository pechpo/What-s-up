//
// Created by zixin on 23-8-23.
//
// src/database/message.cpp
#include "message.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/exception/exception.hpp>
#include <tuple>


MessageDB::MessageDB(DBConnection& connection)
        : messages_(connection.getDatabase("WhatsUpDB").collection("messages")) {
}

bool MessageDB::saveMessage(const std::string& groupId, const std::string& sender, const std::string& content) {
    auto doc = bsoncxx::builder::stream::document{} << "groupId" << groupId << "sender" << sender << "content" << content << bsoncxx::builder::stream::finalize;
    try {
        messages_.insert_one(doc.view());
        return true;
    } catch (mongocxx::exception& e) {
        return false; // 插入失败
    }
}

std::vector<std::tuple<std::string, std::string, std::string>> MessageDB::getMessages(const std::string& groupId) {
    auto query = bsoncxx::builder::stream::document{} << "groupId" << groupId << bsoncxx::builder::stream::finalize;
    auto cursor = messages_.find(query.view());
    std::vector<std::tuple<std::string, std::string, std::string>> result;
    for (const auto& doc : cursor) {
        std::string sender = doc["sender"].get_utf8().value.to_string();
        std::string content = doc["content"].get_utf8().value.to_string();
        result.emplace_back(groupId, sender, content);
    }
    return result;
}
