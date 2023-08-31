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
    ChatBot();

    ~ChatBot();


    static ChatBot * get_instance();

    void processMessage(const int&chat, const QString& content);

private:
    static ChatBot * bt;

    void respondToKeywords(const QString& content, const int &chat);
    void sendMessage(const int &chat, const QString& content);
};

#endif //WHAT_S_UP_BOT_H
