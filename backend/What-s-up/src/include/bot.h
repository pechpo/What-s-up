//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_BOT_H
#define WHAT_S_UP_BOT_H
// include/bot/bot.h
#pragma once

#include <string>
#include "include/message.h" // 包括其他头文件

class ChatBot {
public:
    ChatBot(MessageDB& message_db);

    void processMessage(const Message& message);

    // 其他可能的成员函数声明
};

#endif //WHAT_S_UP_BOT_H
