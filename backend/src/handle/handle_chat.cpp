//
// Created by zixin on 23-8-27.
//

// src/server/handle_chat.cpp

#include <QJsonObject>
#include <QJsonArray>
#include "handle.h"
#include "chat.h"
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
    response["name"] = db->getChatName(chatId);
    QJsonArray chatHistory;
    std::sort(flag.begin(), flag.end(), [](const Message &a, const Message &b) {
        return a.getID() > b.getID();
    });
    for (const auto &x: flag) {
        QJsonObject message;
        message["msgId"] = (int) x.getID();
        message["senderId"] = (int) x.getSenderID();
        message["senderName"] = x.getSenderName();
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
        user["name"] = x.getName();
        user["avatar"] = x.getAvatarName();
        users.append(user);
    }
    response["users"] = users;
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_createChat(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    QJsonArray users = obj["users"].toArray();
    QString name = obj["name"].toString();
    QString avatar = obj["avatar"].toString();
    users.append(ID);
    DB *db = DB::get_instance();
    int chat_id = db->new_chat_id();
    db->e_createChat(chat_id, "111", avatar);
    QSet<int> S;
    for (const auto &x: users) {
        db->e_joinChat(x.toInt(), chat_id);
        S.insert(x.toInt());
        qDebug() << x.toInt();
    }

    QJsonObject response;
    response["type"] = "r_createChat";
    response["success"] = true;  // set to false if insertion fails
    QJsonObject OBJ;
    OBJ["type"] = "a_newChat";
    Server *sv = Server::get_instance();
//    for (const auto &x: S) {
//        qDebug() << x;
//    }
    for (const auto &y: sv->connections_) {
//        qDebug() << y->id;
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
        file["name"] = x.getFileName();
        file["senderId"] = (int) x.getSenderID();
        file["senderName"] = x.getSenderName();
        file["format"] = x.getFormat();
        files.append(file);
    }
    response["files"] = files;
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_chatInfo(const int &id, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();

    DB *db = DB::get_instance();
    auto flag = db->q_chatInfo(chatId);
    QJsonObject response;
    response["type"] = "r_chatInfo";
    response["name"] = std::get<0>(flag);
    response["avatar"] = std::get<1>(flag);
    const auto &U = std::get<2>(flag);
    QJsonArray users;
    for (const auto &x: U) {
        QJsonObject user;
        user["id"] = (int)x.getID();
        user["name"] = x.getName();
        user["avatar"] = x.getAvatarName();
        users.append(user);
    }
    response["users"] = users;
    return response;
}

QJsonObject Handle::e_editChatInfo(const int &id, const QJsonObject &obj) {
    quint32 chatId = obj["chatId"].toInt();
    QString name = obj["name"].toString();
    QString avatar = obj["avatar"].toString();

    DB *db = DB::get_instance();
    auto flag = db->e_editChatInfo(chatId, name, avatar);
    QJsonObject response;
    response["type"] = "r_editChatInfo";
    response["success"] = flag;
    return response;
}

QJsonObject Handle::q_talk(const int &ID, const QJsonObject &obj) {
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_talk(ID, id);
    QJsonObject response;
    response["type"] = "r_talk";
    response["chatId"] = flag;
    return response;
}

QJsonObject Handle::e_exitChat(const int &ID, const QJsonObject &obj) {
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->e_exitChat(ID, chatId);
    QJsonObject response;
    response["type"] = "r_exitChat";
    response["success"] = flag;
    return response;
}