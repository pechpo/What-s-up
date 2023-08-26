//
// Created by zixin on 23-8-23.
//
// src/server/connection.cpp

#include "connection.h"
#include <QDataStream>
#include <QDebug>

Connection::Connection(QTcpSocket* socket, QObject* parent)
        : QTcpSocket(parent), socket_(socket) {
    setSocketDescriptor(socket->socketDescriptor());
    connect(this, &QTcpSocket::readyRead, this, &Connection::receiveMessage);
    qDebug() << "Connection established with:" << this->peerAddress().toString();
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
        for (const auto &x: obj) {
            qDebug() << x;
        }
        qDebug() << '\n';
        curRemainSize = 0;
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
