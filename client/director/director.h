#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <QObject>
#include <QJsonObject>
#include <QMap>

#include "network/connection.h"

class mainWindow;
class Director : public QObject
{
    Q_OBJECT

public:
    enum State {
        Friend, Chat
    };
    typedef void(Director::*Emitter)(const QJsonObject&);
    explicit Director(QObject *parent = nullptr);
    ~Director();
    static Director* getInstance();
    void act(const QJsonObject&); // deal with received JSON message
    void connectServer(const QString& , quint16);
    bool isConnected();
    QString Hash(const QString&);
    bool sendJson(const QJsonObject&);
    void sendPureMessage(const QString&); // debug
    void toMainWindow();
    void refreshMainWindow(enum Director::State);
    void enterChat(qint64);
    void setId(qint64 id);
    void raiseChat(qint64 id);
    qint64 myId();

signals:
    void receiveTestString(const QString&);
    void r_register(const QJsonObject&);
    void r_login(const QJsonObject&);
    void r_myInfo(const QJsonObject&);
    void r_userInfo(const QJsonObject&);
    void r_editInfo(const QJsonObject&);
    void r_list_myChats(const QJsonObject&);
    void r_chatHistory(const QJsonObject&);
    void r_send(const QJsonObject&);
    void r_list_usersInChat(const QJsonObject&);
    void r_addFriend(const QJsonObject&);
    void r_list_friendRequests(const QJsonObject&);
    void r_list_myFriends(const QJsonObject&);
    void r_acceptFriend(const QJsonObject&);
    void r_createChat(const QJsonObject&);
    void r_joinChat(const QJsonObject&);
    void r_list_filesInChat(const QJsonObject&);
    void r_updateFile(const QJsonObject&);
    void r_chatInfo(const QJsonObject&);
    void r_editChatInfo(const QJsonObject&);
    void r_downloadFile(const QJsonObject&);
    void r_talk(const QJsonObject&);
    void r_exitChat(const QJsonObject&);
    void a_newMessage(const QJsonObject&);
    void a_newFriendRequest(const QJsonObject&);
    void a_newChat(const QJsonObject&);

private:
    static Director* self;
    static Connection* conn;
    static Connection* getConnection();
    QHash<QString, Emitter> recvEmitter;
    mainWindow *mainUI;
    bool logged;
    qint64 userId;
};

#endif // DIRECTOR_H
