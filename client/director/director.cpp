#include "director.h"
#include "ui/mainwindow.h"

#include <QCryptographicHash>
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
    recvEmitter.insert("r_updateFile", &Director::r_updateFile);
    recvEmitter.insert("r_downloadFile", &Director::r_downloadFile);
    recvEmitter.insert("r_chatInfo", &Director::r_chatInfo);
    recvEmitter.insert("r_editChatInfo", &Director::r_editChatInfo);
    recvEmitter.insert("r_talk", &Director::r_talk);
    recvEmitter.insert("r_exitChat", &Director::r_exitChat);
    recvEmitter.insert("a_newMessage", &Director::a_newMessage);
    recvEmitter.insert("a_newFriendRequest", &Director::a_newFriendRequest);
    recvEmitter.insert("a_newChat", &Director::a_newChat);

    mainUI = nullptr;
    logged = false;
}

void Director::act(const QJsonObject &obj) {  //after receiving the json package, emit the corresponding signal
    // emit receiveTestString(obj.value("text").toString());
    if (!obj.contains("type")) {
        // todo
        return ;
    }
    QString index = obj.value("type").toString();
    if (!recvEmitter.contains(index)) {
        if ("hello" == index) {
            //emit receiveTestString(obj.value("message").toString());
            emit receiveTestString("");
        }
        return ;
    }
    if ("r_login" == index) {
        if (true == obj.value("success").toBool()) {
            logged = true;
        }
    }
    Emitter e = recvEmitter.value(index);
    emit (this->*e)(obj);
    if (obj["type"].toString() == "r_downloadFile"){
        qDebug() << "receive file ";
    }
    else qDebug() << "recv: " << obj;
}

Director::~Director() {
    delete mainUI;
    delete conn;
    delete self;
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

void Director::connectServer(const QString &IP, quint16 port) {
    getConnection()->connectServer(IP, port);
}

bool Director::isConnected() {
    return getConnection()->isConnected();
}

QString Director::Hash(const QString &o) {
    QString f = o;
    f.append("h?^1~gf;:/vfz");
    QByteArray str;
    str = QCryptographicHash::hash(f.toUtf8(), QCryptographicHash::Md5);
    QString res(str.toHex());
    return res;
}

bool Director::sendJson(const QJsonObject &obj) {
    Connection *conn = getConnection();
    if (conn->isConnected()) {
        conn->sendMessage(obj);
        //simplify file json output
        if (obj["type"].toString() == "e_updateFile"){
            qDebug() << "sendfile ";
        }
        else qDebug() << "send: " << obj;
        return true;
    }
    else {
        return false;
    }
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

void Director::toMainWindow() {
    if (!logged) {
        return;
    }
    if (nullptr == mainUI) {
        mainUI = new mainWindow();
        mainUI->show();
    }
    else {
        refreshMainWindow(Director::Friend);
    }
}

void Director::refreshMainWindow(enum Director::State x) {
    mainUI->setState(x);
}

void Director::enterChat(qint64 id) {
    mainUI->getChatWindow()->switchChat(id);
    refreshMainWindow(Director::Chat);
}
