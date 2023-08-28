//
// Created by zixin on 23-8-27.
//

// src/handle/handle_user.cpp

#include <QJsonObject>
#include <QJsonArray>
#include "handle.h"
#include "db.h"

QJsonObject Handle::e_register(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString name = obj["name"].toString();
    QString password = obj["password"].toString();
    QString avatar = obj["avatar"].toString();
    QString email = obj["email"].toString();
    DB *db = DB::get_instance();
    auto flag = db->e_register(User(id, name, password, avatar, email));

    QJsonObject response;
    response["type"] = "r_register";
    response["success"] = flag;  // set to false if insertion fails
    // Send the response back to client
}

QJsonObject Handle::q_login(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString password = obj["password"].toString();
    DB *db = DB::get_instance();
    auto flag = db->q_login(id, password);

    QJsonObject response;
    response["type"] = "r_login";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

QJsonObject Handle::q_myInfo(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_myInfo(id);

    QJsonObject response;
    response["type"] = "r_myInfo";
    response["id"] = QJsonValue((int) flag.getID());
    response["username"] = flag.getName();
    response["password"] = flag.getPwd();
    response["email"] = flag.getEmail();
    response["avatar"] = flag.getAvatarName();
    // Send the response back to client
}

QJsonObject Handle::q_userInfo(const QJsonObject &json) {
    // Extract the necessary fields from obj
    quint32 id = json["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_userInfo(id);

    QJsonObject response;
    response["type"] = "r_userInfo";
    response["id"] = QJsonValue((int) flag.getID());
    response["username"] = flag.getName();
    response["password"] = flag.getPwd();
    response["email"] = flag.getEmail();
    response["avatar"] = flag.getAvatarName();
    // Send the response back to client
}

QJsonObject Handle::e_editInfo(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString name = obj["name"].toString();
    QString password = obj["password"].toString();
    QString avatar = obj["avatar"].toString();
    QString email = obj["email"].toString();
    DB *db = DB::get_instance();
    auto flag = db->e_editInfo(User(id, name, password, avatar, email));

    QJsonObject response;
    response["type"] = "r_editInfo";
    response["success"] = flag;  // set to false if insertion fails
    if(!flag){
        response["error"] = "Edit failed";
    }
    // Send the response back to client
}

QJsonObject Handle::q_list_myChats(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_myChats(id);

    QJsonObject response;
    response["type"] = "r_list_myChats";
    QJsonArray chats;
    for (const auto &x: flag) {
        QJsonObject chat;
        chat["chatId"] = (int)x.getID();
        chat["name"] = x.getName();
        chat["avatar"] = x.getAvatarName();
        chats.append(chat);
    }
    response["chats"] = chats;

    // Send the response back to client
}

QJsonObject Handle::e_addFriend(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->e_addFriend(id);

    QJsonObject response;
    response["type"] = "r_addFriend";
    response["success"] = flag;  // set to false if insertion fails
    if(!flag){
        response["error"] = "Add failed";
    }
    // Send the response back to client
}

QJsonObject Handle::q_list_friendRequests(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_friendRequests(id);

    QJsonObject response;
    response["type"] = "r_list_friendRequests";
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

QJsonObject Handle::q_list_myFriends(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_list_myFriends(id);

    QJsonObject response;
    response["type"] = "r_list_myFriends";
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

QJsonObject Handle::e_acceptFriend(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->e_acceptFriend(id);

    QJsonObject response;
    response["type"] = "r_acceptFriend";
    response["success"] = flag;  // set to false if insertion fails
    if(!flag){
        response["error"] = "Accept failed";
    }
    // Send the response back to client
}
