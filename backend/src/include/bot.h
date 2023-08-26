//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_BOT_H
#define WHAT_S_UP_BOT_H

#pragma once

#include "message.h"
#include "user.h"
#include "db.h"
#include <string>
#include <chrono>
#include <map>
#include <functional>

class ChatBot {
public:
    ChatBot(const std::string& username, const std::string& password, const std::string& dbPath);

    ~ChatBot();

    void run();

    void sendActivityBasedMessages();


private:
    void respondToCommand(const std::string& command, const std::string& to_user);
    void respondToKeywords(const std::string& content, const std::string& to_user);
    void sendMessage(const std::string& sender, const std::string& receiver, const std::string& content);
    void processMessage(const std::string& sender, const std::string& receiver, const std::string& content);
};

#endif //WHAT_S_UP_BOT_H
