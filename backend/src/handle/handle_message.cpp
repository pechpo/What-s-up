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
    time_t Time = time(0);
    auto flag = db->e_send(Message(message_id, ID, chatId, content, ctime(&Time), db->getName(ID), false, "", ""));

    QJsonObject response;
    response["type"] = "r_send";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Send failed";
    }
    QJsonObject Message;
    Message["msgId"] = message_id;
    Message["senderId"] = ID;
    Message["senderName"] = db->getName(ID);
    Message["content"] = obj["message"].toObject()["content"];
    Message["time"] = ctime(&Time);
    QJsonObject S;
    S["type"] = "a_newMessage";
    S["chatId"] = (int) chatId;
    S["message"] = Message;
    S["is_file"] = false;
    S["format"] = "";
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

QJsonObject Handle::e_updateFile(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    QString content = obj["content"].toString();
    QString name = obj["fileName"].toString();
    QString format = obj["format"].toString();
    DB *db = DB::get_instance();
    int message_id = db->new_message_id();
    time_t Time = time(0);
    auto flag = db->e_send(Message(message_id, ID, chatId, content, ctime(&Time), db->getName(ID), true, name, format));

    QJsonObject response;
    response["type"] = "r_updateFile";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Send failed";
    }
    QJsonObject Message;
    Message["msgId"] = message_id;
    Message["senderId"] = ID;
    Message["senderName"] = db->getName(ID);
    Message["content"] = obj["fileName"];
    Message["time"] = ctime(&Time);
    QJsonObject S;
    S["type"] = "a_newMessage";
    S["chatId"] = (int) chatId;
    S["message"] = Message;
    S["is_file"] = true;
    S["format"] = format;
    Server *sv = Server::get_instance();
    for (const auto &y: sv->connections_) {
        qDebug() << y->id << chatId;
        if (hd->check(y->id, chatId)) {
            y->sendMessage(S);
        }
    }
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_downloadFile(const int &ID, const QJsonObject &obj) {
    quint32 chatId = obj["chatId"].toInt();
    QString name = obj["fileName"].toString();
    DB *db = DB::get_instance();
    auto flag = db->q_downloadFile(chatId, name);

    QJsonObject response;
    response["type"] = "r_downloadFile";
    response["chatId"] = (int) chatId;  // set to false if insertion fails
    response["fileName"] = name;
    response["content"] = flag.first;
    response["format"] = flag.second;
    return response;
}

QJsonObject Handle::e_send_bot(const QString &name, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    auto message = obj["message"].toObject();
    QString content = message["content"].toString();
    DB *db = DB::get_instance();
    int message_id = db->new_message_id();
    time_t Time = time(0);
    auto flag = db->e_send(Message(message_id, 0, chatId, content, ctime(&Time), name, false, "", ""));

    QJsonObject response;
    response["type"] = "r_send";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Send failed";
    }
    QJsonObject Message;
    Message["msgId"] = message_id;
    Message["senderId"] = 0;
    Message["senderName"] = name;
    Message["content"] = obj["message"].toObject()["content"];
    Message["time"] = ctime(&Time);
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