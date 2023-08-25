//
// Created by zixin on 23-8-23.
//
// src/bot/bot.cpp

#include "bot.h"
#include "message.h"
#include <map>
#include <functional>
#include <chrono>

ChatBot::ChatBot(MessageDB& message_db) : message_db(message_db) {}

void ChatBot::processMessage(const std::string& sender, const std::string& receiver, const std::string& content) {
    // 检查消息是否包含机器人的命令或关键字
    if (content.find("/bot") == 0) {
        // 提取命令
        std::string command = content.substr(4);

        // 响应命令
        respondToCommand(command, sender);
    } else {
        // 检查关键字响应
        respondToKeywords(content, sender);
    }
}

void ChatBot::respondToCommand(const std::string& command, const std::string& to_user) {
    // 定义一些简单的命令和响应
    std::map<std::string, std::function<std::string()>> responses = {
            { "hello", []() { return "Hello, how can I help you?"; } },
            { "time",  []() { return "I'm sorry, I don't know the current time."; } },
            // 可以添加更多命令和响应
    };

    auto it = responses.find(command);
    if (it != responses.end()) {
        // 发送响应
        sendMessage("bot", to_user, it->second());
    } else {
        // 未知命令响应
        sendMessage("bot", to_user, "I'm sorry, I don't understand that command.");
    }
}

void ChatBot::respondToKeywords(const std::string& content, const std::string& to_user) {
    // 定义关键字和响应
    std::map<std::string, std::string> keywordResponses = {
            { "weather", "I'm sorry, I can't provide the current weather." },
            { "joke", "Why don't scientists trust atoms? Because they make up everything!" },
            // 可以添加更多关键字和响应
    };

    for (const auto& [keyword, response] : keywordResponses) {
        if (content.find(keyword) != std::string::npos) {
            // 发送关键字响应
            sendMessage("bot", to_user, response);
            break; // 响应第一个匹配的关键字
        }
    }
}

void ChatBot::sendMessage(const std::string& sender, const std::string& receiver, const std::string& content) {
    Message response{
            sender,
            receiver,
            content,
            std::chrono::system_clock::now() // 使用当前时间戳
    };
    message_db.saveMessage(response.sender, response.receiver, response.content);
}
