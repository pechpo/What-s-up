//
// Created by zixin on 23-8-23.
//
// src/server/connection.cpp

#include "connection.h"
#include <QDataStream>
#include <QDebug>

Connection::Connection(QTcpSocket* socket, QObject* parent)
        : QObject(parent), socket_(socket) {
    connect(socket_, &QTcpSocket::readyRead, this, &Connection::readMessage);
    qDebug() << "Connection established with:" << socket_->peerAddress().toString();
}

Connection::~Connection() {
    delete socket_;
}

void Connection::send(const QString& message) {
    write_messages_.enqueue(message);
    writeMessage();
}

void Connection::readMessage() {
    QDataStream in(socket_);
    in.setVersion(QDataStream::Qt_6_0);
    QString message;
    in >> message;
    emit messageReceived(message);
}

void Connection::writeMessage() {
    if (write_messages_.isEmpty() || !socket_->isOpen())
        return;

    QString message = write_messages_.dequeue();
    QDataStream out(socket_);
    out.setVersion(QDataStream::Qt_6_0);
    out << message;
    socket_->flush();
}
