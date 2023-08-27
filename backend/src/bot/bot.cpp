//
// Created by zixin on 23-8-23.
//
// src/bot/bot.cpp

#include "bot.h"
#include "message.h"
#include <map>

void ChatBot::processMessage(const QString& sender, const QString& receiver, const QString& content) {
    if (!content.contains("/bot")) {
        QString command = content.mid(4);
        respondToCommand(command, sender);
    } else {
        respondToKeywords(content, sender);
    }
}

void ChatBot::respondToCommand(const QString& command, const QString& to_user) {
    std::map<QString, std::function<QString()>> responses = {
            {"hello", []() { return "Hello, how can I help you?"; }},
            {"time",  []() { return "I'm sorry, I don't know the current time."; }},
            {"help",  []() { return "I'm sorry, I can't help you."; }},
            {"bye",   []() { return "Goodbye!"; }},
    };

    auto it = responses.find(command);
    if (it != responses.end()) {
        sendMessage("bot", to_user, it->second());
    } else {
        sendMessage("bot", to_user, "I'm sorry, I don't understand that command.");
    }
}

void ChatBot::respondToKeywords(const QString& content, const QString& to_user) {
    std::map<QString, QString> keywordResponses = {
            {"weather", "I'm sorry, I can't provide the current weather."},
            {"joke", "Why don't scientists trust atoms? Because they make up everything!"},
    };

    for (const auto& [keyword, response] : keywordResponses) {
        if (content.contains(keyword)) {
            sendMessage("bot", to_user, response);
            break;
        }
    }
}

void ChatBot::sendMessage(const QString& sender, const QString& receiver, const QString& content) {
}