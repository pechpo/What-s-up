//
// Created by zixin on 23-8-27.
//

#ifndef BACKEND_HANDLE_H
#define BACKEND_HANDLE_H

#include <QObject>
#include "server.h"

class Handle : public QObject{
public:
    Handle();

    ~Handle();

    QJsonObject handle(const int &id, const QJsonObject &json);

    QJsonObject e_register(const int &id, const QJsonObject &json);

    QJsonObject q_login(const int &id, const QJsonObject &json);

    QJsonObject q_myInfo(const int &id, const QJsonObject &json);

    QJsonObject q_userInfo(const int &id, const QJsonObject &json);

    QJsonObject e_editInfo(const int &id, const QJsonObject &json);

    QJsonObject q_list_myChats(const int &id, const QJsonObject &json);

    QJsonObject q_chatHistory(const int &id, const QJsonObject &json);

    QJsonObject e_send(const int &id, const QJsonObject &json);

    QJsonObject q_list_usersInChat(const int &id, const QJsonObject &json);

    QJsonObject e_addFriend(const int &id, const QJsonObject &json);

    QJsonObject q_list_friendRequests(const int &id, const QJsonObject &json);

    QJsonObject q_list_myFriends(const int &id, const QJsonObject &json);

    QJsonObject e_acceptFriend(const int &id, const QJsonObject &json);

    QJsonObject e_createChat(const int &id, const QJsonObject &json);

    QJsonObject e_joinChat(const int &id, const QJsonObject &json);

    QJsonObject q_list_filesInChat(const int &id, const QJsonObject &json);

    QJsonObject e_updateFile(const int &id, const QJsonObject &json);

    QJsonObject q_downloadFile(const int &id, const QJsonObject &json);

    QJsonObject q_chatInfo(const int &id, const QJsonObject &json);

    QJsonObject e_editChatInfo(const int &id, const QJsonObject &json);

    QJsonObject q_talk(const int &id, const QJsonObject &json);

    std::map<QString, std::function<QJsonObject(const int &id, const QJsonObject &)>> handlemap;

    bool check(const int &id, const int &group);

    static Handle * get_instance();

private:

    static Handle * hd;
};

#endif //BACKEND_HANDLE_H