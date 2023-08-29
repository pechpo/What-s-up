//
// Created by zixin on 23-8-27.
//

//src/handle/handle_message.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"
#include "bot.h"

QJsonObject Handle::e_send(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    auto message = obj["message"].toObject();
    QString content = message["content"].toString();
    DB *db = DB::get_instance();
    int message_id = db->new_message_id();
    auto flag = db->e_send(Message(message_id, ID, chatId, content, "111", db->getName(ID), false, ""));

    QJsonObject response;
    response["type"] = "r_send";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Send failed";
    }
    QJsonObject Message;
    Message["msgId"] = message_id;
    Message["senderId"] = ID;
    Message["content"] = obj["message"].toObject()["content"];
    QJsonObject S;
    S["type"] = "a_newMessage";
    S["chatId"] = (int) chatId;
    S["message"] = Message;
    Server *sv = Server::get_instance();
    for (const auto &y: sv->connections_) {
        if (hd->check(y->id, chatId)) {
            y->sendMessage(S);
        }
    }
    ChatBot *bt = ChatBot::get_instance();
    bt->processMessage(chatId, content);
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_send_file(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    auto message = obj["message"].toObject();
    QString content = message["content"].toString();
    QString name = message["name"].toString();
    DB *db = DB::get_instance();
    int message_id = db->new_message_id();
    auto flag = db->e_send(Message(message_id, ID, chatId, content, "111", db->getName(ID), true, name));

    QJsonObject response;
    response["type"] = "r_send";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Send failed";
    }
    obj["type"] = "a_newMessage";
    QJsonObject Message;
    Message["msgId"] = message_id;
    Message["senderId"] = ID;
    Message["content"] = obj["message"].toObject()["content"];
    QJsonObject S;
    S["type"] = "a_newMessage";
    S["chatId"] = (int) chatId;
    S["message"] = Message;
    Server *sv = Server::get_instance();
    for (const auto &y: sv->connections_) {
        if (hd->check(y->id, chatId)) {
            y->sendMessage(S);
        }
    }
    return response;
    // Send the response back to client
}