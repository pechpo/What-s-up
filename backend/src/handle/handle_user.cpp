//
// Created by zixin on 23-8-27.
//

// src/handle/handle_user.cpp

#include <QJsonObject>
#include <QJsonArray>
#include "handle.h"
#include "db.h"
#include "log.h"

QJsonObject Handle::e_register(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString name = obj["username"].toString();
    QString password = obj["password"].toString();
    QString avatar = obj["avatar"].toString();
    QString email = obj["email"].toString();
    DB *db = DB::get_instance();
    auto flag = db->e_register(User(id, name, password, avatar, email));
    QJsonObject response;
    response["type"] = "r_register";
    response["success"] = flag;  // set to false if insertion fails
    if (flag) {
        writeLog("User Registration", "User with ID " + QString::number(id) + " registered successfully.", true);
    } else {
        writeLog("User Registration", "Failed to register user with ID " + QString::number(id) + ".", false);
    }
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_login(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString password = obj["password"].toString();
    DB *db = DB::get_instance();
    auto flag = db->q_login(id, password);

    QJsonObject response;
    response["type"] = "r_login";
    response["success"] = flag;  // set to false if query fails
    if (flag) {
        writeLog("User Login", "User with ID " + QString::number(id) + " logged in successfully.", true);
    } else {
        writeLog("User Login", "Failed to log in user with ID " + QString::number(id) + ".", false);
    }
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_myInfo(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    DB *db = DB::get_instance();
    auto flag = db->q_myInfo(ID);

    QJsonObject response;
    response["type"] = "r_myInfo";
    response["id"] = QJsonValue((int) flag.getID());
    response["username"] = flag.getName();
    response["password"] = flag.getPwd();
    response["email"] = flag.getEmail();
    response["avatar"] = flag.getAvatarName();
    writeLog("Edit User Info", "User with ID " + QString::number(ID) + " edited their information.", true);
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_userInfo(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->q_userInfo(id);

    QJsonObject response;
    response["type"] = "r_userInfo";
    response["id"] = QJsonValue((int) flag.getID());
    response["username"] = flag.getName();
    response["email"] = flag.getEmail();
    response["avatar"] = flag.getAvatarName();
    QJsonArray sharedChats;
    auto tmp = db->q_list_myChats(ID);
    auto Tmp = db->q_list_myChats(id);
    for (const auto &x: tmp) {
        for (const auto &y: Tmp) {
            if (x.getID() == y.getID()) {
                QJsonObject chat;
                chat["chatId"] = (int) x.getID();
                chat["name"] = x.getName();
                chat["avatar"] = x.getAvatarName();
                sharedChats.append(chat);
                break;
            }
        }
    }
    response["sharedChats"] = sharedChats;
    writeLog("Query Info", "User with ID " + QString::number(ID) + " queried information of user with ID " + QString::number(id) + ".", true);
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_editInfo(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    QString name = obj["name"].toString();
    QString password = obj["password"].toString();
    QString avatar = obj["avatar"].toString();
    QString email = obj["email"].toString();
    DB *db = DB::get_instance();
    auto user = User(ID, name, password, avatar, email);

    db->e_edit_name(user);
    db->e_edit_password(user);
    db->e_edit_avatar(user);
    db->e_edit_email(user);

    QJsonObject response;
    response["type"] = "r_editInfo";
    response["success"] = true;  // set to false if insertion fails
    writeLog("Edit User Info", "User with ID " + QString::number(ID) + " edited their information.", true);
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_list_myChats(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    DB *db = DB::get_instance();
    auto flag = db->q_list_myChats(ID);

    QJsonObject response;
    response["type"] = "r_list_myChats";
    QJsonArray chats;
    for (const auto &x: flag) {
        QJsonObject chat;
        chat["chatId"] = (int) x.getID();
        chat["name"] = x.getName();
        chat["avatar"] = x.getAvatarName();
        chats.append(chat);
    }
    response["chats"] = chats;
    writeLog("Query Chat", "User with ID " + QString::number(ID) + " queried their chats.", true);
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_addFriend(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    if (id == ID) {
        QJsonObject response;
        response["type"] = "r_addFriend";
        response["success"] = false;
        response["error"] = "Can't add myself!";
        return response;
    }
    DB *db = DB::get_instance();
    auto flag = db->e_addFriend(ID, id);

    QJsonObject response;
    response["type"] = "r_addFriend";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Add failed";
    }
    QJsonObject OBJ;
    OBJ["type"] = "a_newFriendRequest";
    Server *sv = Server::get_instance();
    for (const auto &y: sv->connections_) {
        qDebug() << y->id << id;
        if (y->id == id) {
            y->sendMessage(OBJ);
        }
    }
    if (flag) {
        writeLog("Add Friend", "User with ID " + QString::number(ID) + " sent friend request to ID " + QString::number(id) + ".", true);
    } else {
        writeLog("Add Friend", "User with ID " + QString::number(ID) + " failed to send friend request to ID " + QString::number(id) + ".", false);
    }
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_list_friendRequests(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    DB *db = DB::get_instance();
    auto flag = db->q_list_friendRequests(ID);

    QJsonObject response;
    response["type"] = "r_list_friendRequests";
    QJsonArray users;
    for (const auto &x: flag) {
        QJsonObject user;
        user["id"] = (int) x.getID();
        user["name"] = x.getName();
        user["avatar"] = x.getAvatarName();
        users.append(user);
    }
    response["users"] = users;
    writeLog("List Friend Requests", "User with ID " + QString::number(ID) + " listed their friend requests.", true);
    return response;
    // Send the response back to client
}

QJsonObject Handle::q_list_myFriends(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    DB *db = DB::get_instance();
    auto flag = db->q_list_myFriends(ID);

    QJsonObject response;
    response["type"] = "r_list_myFriends";
    QJsonArray users;
    for (const auto &x: flag) {
        QJsonObject user;
        user["id"] = (int) x.getID();
        user["name"] = x.getName();
        user["avatar"] = x.getAvatarName();
        users.append(user);
    }
    response["users"] = users;
    writeLog("List My Friends", "User with ID " + QString::number(ID) + " listed their friends.", true);
    return response;
    // Send the response back to client
}

QJsonObject Handle::e_acceptFriend(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    bool fl = obj["accept"].toBool();
    qDebug() << fl;
    DB *db = DB::get_instance();
    auto flag = db->e_acceptFriend(ID, id, fl);

    QJsonObject response;
    response["type"] = "r_acceptFriend";
    response["success"] = flag;  // set to false if insertion fails
    if (!flag) {
        response["error"] = "Accept failed";
    }
    if (flag) {
        writeLog("Accept Friend", "User with ID " + QString::number(ID) + " accepted/rejected friend request from ID " + QString::number(id) + ".", true);
    } else {
        writeLog("Accept Friend", "User with ID " + QString::number(ID) + " failed to accept/reject friend request from ID " + QString::number(id) + ".", false);
    }

    return response;
    // Send the response back to client
}
