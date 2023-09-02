//
// Created by zixin on 23-8-23.
//
// src/server/connection.cpp

#include "connection.h"
#include <QDataStream>
#include <QDebug>
#include "handle.h"
#include "server.h"

Connection::Connection(qintptr ii) {
    setSocketDescriptor(ii);
    connect(this, &QTcpSocket::readyRead, this, &Connection::receiveMessage);
    qDebug() << "Connection established with:" << this->peerAddress().toString();
    sendMessage(QJsonObject({{"type", "hello"}}));
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
            qDebug() << "Received invalid JSON object. Error:" << err.errorString();
            return;
        }
        QJsonObject obj = doc.object();
        qDebug() << "Received message from client:" << obj;
        //qDebug() << obj;
        if (obj["type"] == "q_login") {
            id = obj["id"].toInt();
        }
        Handle *hd = Handle::get_instance();
        //qDebug() << obj;
        auto x = hd->handle(id, obj);
        qDebug() << x;
        curRemainSize = 0;
        sendMessage(x);
    }
}

void Connection::sendMessage(const QJsonObject &obj) {
    qDebug() << "Sending message to client:" << obj;  // Debug message added
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
    qDebug() << "Message sent.";
}