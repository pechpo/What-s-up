//
// Created by zixin on 23-8-27.
//

// src/server/handle_group.cpp

#include <QJsonObject>
#include <QJsonArray>
#include "handle.h"
#include "group.h"
#include "db.h"

QJsonObject Handle::q_chatHistory(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    quint32 time = obj["time"].toInt();
    quint32 count = obj["count"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_chatHistory(chatId, time, count);

    QJsonObject response;
    response["type"] = "r_chatHistory";
    response["chatId"] = (int) chatId;
    QJsonArray chatHistory;
    for (const auto &x: flag) {
        QJsonObject message;
        message["id"] = (int) x.getID();
        message["senderId"] = (int) x.getSenderID();
        message["receiverId"] = (int) x.getReceiverID();
        message["content"] = x.getContent();
        message["time"] = x.getTime();
        chatHistory.append(message);
    }
    response["chatHistory"] = chatHistory;
    return response;
    // Send the response back to client
}


QJsonObject Handle::q_list_usersInChat(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_usersInChat(chatId);

    QJsonObject response;
    response["type"] = "r_list_usersInChat";
    QJsonArray users;
    for (const auto &x: flag) {
        QJsonObject user;
        user["id"] = (int) x.getID();
        user["username"] = x.getName();
        user["password"] = x.getPwd();
        user["email"] = x.getEmail();
        user["avatar"] = x.getAvatarName();
        users.append(user);
    }
    response["users"] = users;
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_createChat(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    QJsonObject users = obj["users"].toObject();
    DB *db = DB::get_instance();
    int chat_id = db->new_group_id();
    QSet<int> S;
    for (const auto &x: users) {
        db->e_joinChat(x.toInt(), chat_id);
        S.insert(x.toInt());
    }

    QJsonObject response;
    response["type"] = "r_createChat";
    response["success"] = true;  // set to false if insertion fails
    QJsonObject OBJ;
    OBJ["type"] = "a_newChat";
    Server *sv = Server::get_instance();
    for (const auto &y: sv->connections_) {
        if (S.contains(y->id)) {
            y->sendMessage(OBJ);
        }
    }
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_joinChat(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->e_joinChat(ID, chatId);

    QJsonObject response;
    response["type"] = "r_joinChat";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Join failed";
    }
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_list_filesInChat(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_filesInChat(chatId);

    QJsonObject response;
    response["type"] = "r_list_filesInChat";
    QJsonArray files;
    for (const auto &x: flag) {
        QJsonObject file;
        file["fileId"] = (int) x.getID();
        file["time"] = x.getTime();
        file["senderId"] = (int) x.getSenderID();
        file["receiverId"] = (int) x.getReceiverID();
        files.append(file);
    }
    response["files"] = files;
    return response;
    // Send the response back to client
}