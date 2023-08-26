#include "director.h"
#include <QJsonObject>

#include <QDebug>

Director::Director(QObject *parent)
    : QObject{parent} {

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
    if (obj.contains("text")) {
        emit receiveTestString(obj.value("text").toString());
    }
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
