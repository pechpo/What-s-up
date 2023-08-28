//
// Created by zixin on 23-8-23.
//
// src/server/connection.cpp

#include "connection.h"
#include <QDataStream>
#include <QDebug>
#include "handle.h"

Connection::Connection(QTcpSocket* socket, QObject* parent)
        : QTcpSocket(parent) {
    setSocketDescriptor(socket->socketDescriptor());
    socket->setParent(this);  // 设置父对象
    connect(this, &QTcpSocket::readyRead, this, &Connection::receiveMessage);
    qDebug() << "Connection established with:" << this->peerAddress().toString();
    sendMessage(QJsonObject{{"type", "hello"}, {"message", "Hello, world!"}});
}

Connection::~Connection() {
    delete socket_;
}

void Connection::receiveMessage() {
    while (bytesAvailable() > 0) {
        QDataStream in(this);
        in.setVersion(QDataStream::Qt_6_5);
        if (0 == curRemainSize) {
            if (bytesAvailable() >= sizeof(quint32)) {
                in >> curRemainSize;
            } else {
                return;
            }
        }
        if (bytesAvailable() < curRemainSize) {
            return; // wait to read full message
        }
        QByteArray jsonBytes;
        in >> jsonBytes;
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(jsonBytes, &err);
        if (!doc.isObject()) {
            // Handle the error
        }
        QJsonObject obj = doc.object();
        Handle *hd = Handle::get_instance();
        auto x = hd->handle(obj);
        curRemainSize = 0;
        sendMessage(x);
    }
}

void Connection::sendMessage(const QJsonObject &obj) {
    waitForBytesWritten();
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray outMsg;
    QDataStream out(&outMsg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint32(0) << doc.toJson();
    out.device()->seek(0);
    out << quint32(outMsg.size() - sizeof(quint32));
    write(outMsg);
}
