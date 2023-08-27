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
    ChatBot(const QString& username, const QString& password, const QString& dbPath);

    ~ChatBot();

    void run();

private:
    void respondToCommand(const QString& command, const QString& to_user);
    void respondToKeywords(const QString& content, const QString& to_user);
    void sendMessage(const QString& sender, const QString& receiver, const QString& content);
    void processMessage(const QString& sender, const QString& receiver, const QString& content);
};

#endif //WHAT_S_UP_BOT_H
