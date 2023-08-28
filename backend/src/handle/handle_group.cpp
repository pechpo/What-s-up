//
// Created by zixin on 23-8-27.
//

// src/server/handle_group.cpp

#include <QJsonObject>
#include <QJsonArray>
#include "handle.h"
#include "group.h"
#include "db.h"

QJsonObject Handle::q_chatHistory(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    quint32 time = obj["time"].toInt();
    quint32 count = obj["count"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_chatHistory(chatId, time, count);

    QJsonObject response;
    response["type"] = "r_chatHistory";
    response["chatId"] = (int)chatId;
    QJsonArray chatHistory;
    for (const auto &x: flag) {
        QJsonObject message;
        message["id"] = (int)x.getID();
        message["senderId"] = (int)x.getSenderID();
        message["receiverId"] = (int)x.getReceiverID();
        message["content"] = x.getContent();
        message["time"] = x.getTime();
        chatHistory.append(message);
    }
    response["chatHistory"] = chatHistory;

    // Send the response back to client
}



QJsonObject Handle::q_list_usersInChat(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_usersInChat(chatId);

    QJsonObject response;
    response["type"] = "r_list_usersInChat";
    QJsonArray users;
    for (const auto &x: flag) {
        QJsonObject user;
        user["id"] = (int)x.getID();
        user["username"] = x.getName();
        user["password"] = x.getPwd();
        user["email"] = x.getEmail();
        user["avatar"] = x.getAvatarName();
        users.append(user);
    }
    response["users"] = users;

    // Send the response back to client
}

QJsonObject Handle::e_createChat(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString name = obj["name"].toString();
    QString ava = obj["avatar"].toString();
    DB *db = DB::get_instance();
    auto flag = db->e_createChat(id, name, ava);

    QJsonObject response;
    response["type"] = "r_createChat";
    response["success"] = flag;  // set to false if insertion fails
    if(!flag){
        response["error"] = "Create failed";
    }
    // Send the response back to client
}

QJsonObject Handle::e_joinChat(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->e_joinChat(chatId, id);

    QJsonObject response;
    response["type"] = "r_joinChat";
    response["success"] = flag;  // set to false if insertion fails
    if(!flag){
        response["error"] = "Join failed";
    }
    // Send the response back to client
}

QJsonObject Handle::q_list_filesInChat(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_filesInChat(chatId);

    QJsonObject response;
    response["type"] = "r_list_filesInChat";
    QJsonArray files;
    for (const auto &x: flag) {
        QJsonObject file;
        file["id"] = (int)x.getID();
        file["time"] = x.getTime();
        file["senderId"] = (int)x.getSenderID();
        file["receiverId"] = (int)x.getReceiverID();
        files.append(file);
    }
    response["files"] = files;

    // Send the response back to client
}