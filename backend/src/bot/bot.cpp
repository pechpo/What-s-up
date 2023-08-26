//
// Created by zixin on 23-8-23.
//
// src/bot/bot.cpp

#include "bot.h"
#include "message.h"
#include <map>

void ChatBot::processMessage(const std::string& sender, const std::string& receiver, const std::string& content) {
    if (content.find("/bot") == 0) {
        std::string command = content.substr(4);
        respondToCommand(command, sender);
    } else {
        respondToKeywords(content, sender);
    }
}

void ChatBot::respondToCommand(const std::string& command, const std::string& to_user) {
    std::map<std::string, std::function<std::string()>> responses = {
            {"hello", []() { return "Hello, how can I help you?"; }},
            {"time",  []() { return "I'm sorry, I don't know the current time."; }},
    };

    auto it = responses.find(command);
    if (it != responses.end()) {
        sendMessage("bot", to_user, it->second());
    } else {
        sendMessage("bot", to_user, "I'm sorry, I don't understand that command.");
    }
}

void ChatBot::respondToKeywords(const std::string& content, const std::string& to_user) {
    std::map<std::string, std::string> keywordResponses = {
            {"weather", "I'm sorry, I can't provide the current weather."},
            {"joke", "Why don't scientists trust atoms? Because they make up everything!"},
    };

    for (const auto& [keyword, response] : keywordResponses) {
        if (content.find(keyword) != std::string::npos) {
            sendMessage("bot", to_user, response);
            break;
        }
    }
}

void ChatBot::sendMessage(const std::string& sender, const std::string& receiver, const std::string& content) {
}