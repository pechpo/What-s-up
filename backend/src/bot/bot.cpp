//
// Created by zixin on 23-8-23.
//
// src/bot/bot.cpp
#include "message.h"
#include <map>
#include <functional>
#include <chrono>

class ChatBot {
    MessageDB& message_db;

public:
    ChatBot(MessageDB& message_db) : message_db(message_db) {}

    void processMessage(const Message& message) {
        // 检查消息是否包含机器人的命令或关键字
        if (message.content.find("/bot") == 0) {
            // 提取命令
            std::string command = message.content.substr(4);

            // 响应命令
            respondToCommand(command, message.sender);
        }
    }

private:
    void respondToCommand(const std::string& command, const std::string& to_user) {
        // 定义一些简单的命令和响应
        std::map<std::string, std::function<std::string()>> responses = {
                { "hello", []() { return "Hello, how can I help you?"; } },
                { "time",  []() { return "I'm sorry, I don't know the current time."; } },
                // 可以添加更多命令和响应
        };

        auto it = responses.find(command);
        if (it != responses.end()) {
            // 发送响应
            Message response{
                    "bot",
                    to_user,
                    it->second(),
                    std::chrono::system_clock::now() // 使用当前时间戳
            };
            message_db.saveMessage(response.sender, response.receiver, response.content, false);
        } else {
            // 未知命令响应
            Message response{
                    "bot",
                    to_user,
                    "I'm sorry, I don't understand that command.",
                    std::chrono::system_clock::now() // 使用当前时间戳
            };
            message_db.saveMessage(response.sender, response.receiver, response.content, false);
        }
    }
};

// 其他机器人相关的代码...
