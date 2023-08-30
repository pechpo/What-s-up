#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "user.h"
#include "message.h"
#include "chat.h"

class DB {

public :
    DB();

    ~DB();

    bool e_register(const User &user);

    bool q_login(const quint32 &ID, const QString &password);

    bool e_edit_name(const User &user);

    bool e_edit_password(const User &user);

    bool e_edit_avatar(const User &user);

    bool e_edit_email(const User &user);

    User q_myInfo(const quint32 &ID);

    User q_userInfo(const quint32 &ID);

    bool e_send(const Message &message);

    QList<Message> q_chatHistory(const quint32 &chat_ID, const quint32 &time, const quint32 &count);

    QList<chat> q_list_myChats(const quint32 &ID);

    QList<User> q_list_usersInChat(const quint32 &chat_ID);

    bool e_addFriend(const quint32 &id, const quint32 &ID);

    QList<User> q_list_friendRequests(const quint32 &ID);

    QList<User> q_list_myFriends(const quint32 &ID);

    bool e_acceptFriend(const quint32 &id, const quint32 &ID, const bool &fl);

    bool e_createChat(const quint32 &ID, const QString &name, const QString &avatar);

    bool e_joinChat(const quint32 &ID, const quint32 &chat_ID);

    QList<Message> q_list_filesInChat(const quint32 &chat_ID);

    QString getName(const quint32 &ID);

    bool check(const int &id, const int &chat);

    static DB *get_instance();

    int new_chat_id();

    int new_message_id();

    bool uploadFileToFTP(const QString &filename);

    std::tuple<QString, QString, QList<User>> q_chatInfo(const quint32 &ID);

    bool e_editChatInfo(const quint32 &ID, const QString &name, const QString &avatar);

    std::pair<QString, QString> q_downloadFile(const int &ID, const QString &filename);

    int q_talk(const int &id, const int &ID);

    QString getChatName(const int &ID);

    bool add_tag(const int &ID, const std::vector<int> &tags);

    std::vector<int> get_tags(const int &ID);

    std::unordered_map<quint32, std::vector<int>> get_all_tags();

    std::vector<quint32> getFriends(const int &ID);

    bool e_exitChat(const int &ID, const int &chatId);

private:

    static DB *db;

    QSqlDatabase database;
};

#endif // DB_H