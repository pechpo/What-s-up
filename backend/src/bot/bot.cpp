//
// Created by zixin on 23-8-23.
//
// src/bot/bot.cpp

#include "bot.h"
#include "message.h"
#include "handle.h"
#include "server.h"
#include <map>

ChatBot::ChatBot() {
}

ChatBot *ChatBot::bt = nullptr;

ChatBot *ChatBot::get_instance() {
    if (bt == nullptr) {
        bt = new ChatBot;
    }
    return bt;
}

void ChatBot::processMessage(const int &group, const QString &content) {
    respondToKeywords(content, group);
}

//void ChatBot::respondToCommand(const QString& command, const QString& to_user) {
//    std::map<QString, std::function<QString()>> responses = {
//            {"hello", []() { return "Hello, how can I help you?"; }},
//            {"time",  []() { return "I'm sorry, I don't know the current time."; }},
//            {"help",  []() { return "I'm sorry, I can't help you."; }},
//            {"bye",   []() { return "Goodbye!"; }},
//    };
//
//    auto it = responses.find(command);
//    if (it != responses.end()) {
//        sendMessage("bot", to_user, it->second());
//    }
////    else {
////        sendMessage("bot", to_user, "I'm sorry, I don't understand that command.");
////    }
//}

void ChatBot::respondToKeywords(const QString &content, const int &group) {
    std::map<QString, QString> keywordResponses = {
            {"hello",   "Hello, how can I help you?"},
            {"time",    "I'm sorry, I don't know the current time."},
            {"help",    "I'm sorry, I can't help you."},
            {"bye",     "Goodbye!"},
            {"weather", "I'm sorry, I can't provide the current weather."},
            {"joke",    "Why don't scientists trust atoms? Because they make up everything!"},
    };

    for (const auto &[keyword, response]: keywordResponses) {
        if (content.contains(keyword)) {
            sendMessage(group, response);
            break;
        }
    }
}

void ChatBot::sendMessage(const int &group, const QString &content) {
    QJsonObject Message;
    Message["msgId"] = 0;
    Message["senderId"] = 0;
    Message["content"] = content;
    QJsonObject S;
    S["type"] = "a_newMessage";
    S["chatId"] = (int) group;
    S["message"] = Message;
    Server *sv = Server::get_instance();
    Handle *hd = Handle::get_instance();
    for (const auto &y: sv->connections_) {
        if (hd->check(y->id, group)) {
            y->sendMessage(S);
        }
    }
}