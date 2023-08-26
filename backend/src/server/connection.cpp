//
// Created by zixin on 23-8-23.
//
// src/server/connection.cpp

#include "connection.h"
#include <QDataStream>
#include <QDebug>

Connection::Connection(QTcpSocket* socket, QObject* parent)
        : QTcpSocket(parent), socket_(socket) {
    connect(this, &QTcpSocket::readyRead, this, &Connection::receiveMessage); // 注意这里改为 'this'
    qDebug() << "Connection established with:" << this->peerAddress().toString(); // 注意这里改为 'this'
}

Connection::~Connection() {
    delete socket_;
}

void Connection::receiveMessage() {
    while (bytesAvailable() > 0) { // may read more than one message
        QDataStream in(this);
        in.setVersion(QDataStream::Qt_6_5);
        if (0 == curRemainSize) {
            if (bytesAvailable() >= sizeof(quint32)) {
                in >> curRemainSize;
            }
            else {
                return ;
            }
        }
        if (bytesAvailable() < curRemainSize) {
            return ; // wait to read full message
        }
        // read a JSON
        QByteArray jsonBytes;
        in >> jsonBytes;
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(jsonBytes, &err);
        // *todo: deal with err
        if (!doc.isObject()) {
            // *todo: not object
        }
        QJsonObject obj = doc.object();
        for (const auto &x: obj) {
            qDebug() << x;
        }
        qDebug() << '\n';
        curRemainSize = 0;
    }
}

void Connection::sendMessage(const QJsonObject &obj) {
    // called only if isConnected()
    waitForBytesWritten();
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray outMsg;
    QDataStream out(&outMsg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint32(0) << doc.toJson();
    // quint32(0) is for size
    out.device()->seek(0);
    out << quint32(outMsg.size() - sizeof(quint32));
    write(outMsg);
}
