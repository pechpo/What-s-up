//
// Created by zixin on 23-8-27.
//

#ifndef BACKEND_HANDLE_H
#define BACKEND_HANDLE_H

#include <QObject>

class Handle : public QObject{
public:
    Handle();

    QJsonObject handle(const QJsonObject &json);

    QJsonObject e_register(const QJsonObject &json);

    QJsonObject q_login(const QJsonObject &json);

    QJsonObject q_myInfo(const QJsonObject &json);

    QJsonObject q_userInfo(const QJsonObject &json);

    QJsonObject e_editInfo(const QJsonObject &json);

    QJsonObject q_list_myChats(const QJsonObject &json);

    QJsonObject q_chatHistory(const QJsonObject &json);

    QJsonObject e_send(const QJsonObject &json);

    QJsonObject q_list_usersInChat(const QJsonObject &json);

    QJsonObject e_addFriend(const QJsonObject &json);

    QJsonObject q_list_friendRequests(const QJsonObject &json);

    QJsonObject a_newFriendRequest(const QJsonObject &json);

    QJsonObject q_list_myFriends(const QJsonObject &json);

    QJsonObject e_acceptFriend(const QJsonObject &json);

    QJsonObject e_createChat(const QJsonObject &json);

    QJsonObject e_joinChat(const QJsonObject &json);

    QJsonObject a_newChat(const QJsonObject &json);

    QJsonObject q_list_filesInChat(const QJsonObject &json);

    std::map<QString, std::function<QJsonObject(const QJsonObject &)>> handlemap;

    static Handle * get_instance();

private:

    static Handle * hd;
};

#endif //BACKEND_HANDLE_H