//
// Created by zixin on 23-8-27.
//

// src/server/handle_chat.cpp

#include <QJsonObject>
#include <QJsonArray>
#include "handle.h"
#include "chat.h"
#include "db.h"
#include "log.h"

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
        return a.getID() < b.getID();
    });
    for (const auto &x: flag) {
        QJsonObject message;
        message["msgId"] = (int) x.getID();
        message["senderId"] = (int) x.getSenderID();
        message["senderName"] = x.getSenderName();
        message["content"] = x.getContent();
        message["is_file"] = x.getIsFile();
        message["time"] = x.getTime();
        message["format"] = x.getFormat();
        message["filename"] = x.getFileName();
        chatHistory.append(message);
    }
    response["chatHistory"] = chatHistory;
    writeLog("Query Chat History", "User with ID " + QString::number(ID) + " queried the chat history of chat " + QString::number(chatId) + ".", true);
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
    writeLog("List Users in Chat", "User with ID " + QString::number(ID) + " listed users in chat " + QString::number(chatId) + ".", true);
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
    for (const auto &y: sv->connections_) {
        if (S.contains(y->id)) {
            y->sendMessage(OBJ);
        }
    }
    writeLog("Create Chat", "User with ID " + QString::number(ID) + " created a new chat.", true);
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
    if (flag) {
        writeLog("Join Chat", "User with ID " + QString::number(ID) + " joined chat " + QString::number(chatId) + ".", true);
    } else {
        writeLog("Join Chat", "User with ID " + QString::number(ID) + " failed to join chat " + QString::number(chatId) + ".", false);
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
    writeLog("List Files in Chat", "User with ID " + QString::number(ID) + " listed files in chat " + QString::number(chatId) + ".", true);
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
    writeLog("Query Chat Info", "User with ID " + QString::number(id) + " queried the info of chat " + QString::number(chatId) + ".", true);
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
    if (flag) {
        writeLog("Edit Chat Info", "User with ID " + QString::number(id) + " edited the info of chat " + QString::number(chatId) + ".", true);
    } else {
        writeLog("Edit Chat Info", "User with ID " + QString::number(id) + " failed to edit the info of chat " + QString::number(chatId) + ".", false);
    }
    return response;
}

QJsonObject Handle::q_talk(const int &ID, const QJsonObject &obj) {
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_talk(ID, id);
    QJsonObject response;
    response["type"] = "r_talk";
    response["chatId"] = flag;
    writeLog("Query Chat", "User with ID " + QString::number(ID) + " queried the chat with user with ID " + QString::number(id) + ".", true);
    return response;
}

QJsonObject Handle::e_exitChat(const int &ID, const QJsonObject &obj) {
    quint32 chatId = obj["chatId"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->e_exitChat(ID, chatId);
    QJsonObject response;
    response["type"] = "r_exitChat";
    response["success"] = flag;
    if (flag) {
        writeLog("Exit Chat", "User with ID " + QString::number(ID) + " exited chat " + QString::number(chatId) + ".", true);
    } else {
        writeLog("Exit Chat", "User with ID " + QString::number(ID) + " failed to exit chat " + QString::number(chatId) + ".", false);
    }

    return response;
}