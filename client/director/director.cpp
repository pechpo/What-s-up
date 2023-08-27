#include "director.h"

#include <QDebug>

Director::Director(QObject *parent)
    : QObject{parent} {
    recvEmitter.insert("r_register", &Director::r_register);
    recvEmitter.insert("r_login", &Director::r_login);
    recvEmitter.insert("r_myInfo", &Director::r_myInfo);
    recvEmitter.insert("r_userInfo", &Director::r_userInfo);
    recvEmitter.insert("r_editInfo", &Director::r_editInfo);
    recvEmitter.insert("r_list_myChats", &Director::r_list_myChats);
    recvEmitter.insert("r_chatHistory", &Director::r_chatHistory);
    recvEmitter.insert("r_send", &Director::r_send);
    recvEmitter.insert("r_list_usersInChat", &Director::r_list_usersInChat);
    recvEmitter.insert("r_addFriend", &Director::r_addFriend);
    recvEmitter.insert("r_list_friendRequests", &Director::r_list_friendRequests);
    recvEmitter.insert("r_list_myFriends", &Director::r_list_myFriends);
    recvEmitter.insert("r_acceptFriend", &Director::r_acceptFriend);
    recvEmitter.insert("r_createChat", &Director::r_createChat);
    recvEmitter.insert("r_joinChat", &Director::r_joinChat);
    recvEmitter.insert("r_list_filesInChat", &Director::r_list_filesInChat);
    recvEmitter.insert("a_newMessage", &Director::a_newMessage);
    recvEmitter.insert("a_newFriendRequest", &Director::a_newFriendRequest);
    recvEmitter.insert("a_newChat", &Director::a_newChat);
}

Director::~Director() {

}

Director* Director::self = nullptr;
Director* Director::getInstance() {
    if (!self) {
        self = new Director();
    }
    return self;
}

Connection* Director::conn = nullptr;
Connection* Director::getConnection() {
    if (!conn) {
        conn = new Connection();
    }
    return conn;
}

void Director::act(const QJsonObject &obj) {
    qDebug() << "recv: " << obj;
    // emit receiveTestString(obj.value("text").toString());
    if (!obj.contains("type")) {
        // todo
        return ;
    }
    QString index = obj.value("type").toString();
    if (!recvEmitter.contains(index)) {
        return ;
    }
    Emitter e = recvEmitter.value(index);
    emit (this->*e)(obj);
}

void Director::connectServer(const QString &IP, quint16 port) {
    getConnection()->connectServer(IP, port);
}

void Director::sendPureMessage(const QString &text) {
    Connection *conn = getConnection();
    //emit receiveTestString("send: " + text);
    if (conn->isConnected()) {
        // do not send plain text
        QJsonObject obj;
        obj.insert("text", text);
        qDebug() << "send: " << obj;
        conn->sendMessage(obj);
    }
}
