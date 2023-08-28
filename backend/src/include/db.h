#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "user.h"
#include "message.h"
#include "group.h"

class DB {

public :
    DB();

    ~DB();

    bool e_register(const User &user);

    bool q_login(const quint32 &ID, const QString &password);

    bool e_editInfo(const User &user);

    User q_myInfo(const quint32 &ID);

    User q_userInfo(const quint32 &ID);

    bool e_send(const Message &message);

    QList<Message> q_chatHistory(const quint32 &chat_ID, const quint32 &time, const quint32 &count);

    QList<Group> q_list_myChats(const quint32 &ID);

    QList<User> q_list_usersInChat(const quint32 &chat_ID);

    bool e_addFriend(const quint32 &ID);

    QList<User> q_list_friendRequests(const quint32 &ID);

    QList<User> q_list_myFriends(const quint32 &ID);

    bool e_acceptFriend(const quint32 &ID);

    bool e_createChat(const quint32 &ID, const QString &name, const QString &avatar);

    bool e_joinChat(const quint32 &ID, const quint32 &chat_ID);

    bool e_quitChat(const quint32 &ID, const quint32 &chat_ID);

    bool e_delChat(const quint32 &ID, const quint32 &chat_ID);

    QList<Message> q_list_filesInChat(const quint32 &chat_ID);

    static DB * get_instance();

private:

    static DB * db;

    QSqlDatabase database;
};
#endif // DB_H