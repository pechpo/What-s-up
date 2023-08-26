//
// Created by zixin on 23-8-23.
//
// src/server/server.cpp

#include "server.h"
#include "connection.h"
#include <QDebug>

Server::Server(const QString& address, quint16 port, QObject* parent)
        : QObject(parent) {
    connect(&tcpServer_, &QTcpServer::newConnection, this, &Server::acceptConnection);
    if (address == "0.0.0.0") {
        tcpServer_.listen(QHostAddress::Any, port);
    } else {
        tcpServer_.listen(QHostAddress(address), port);
    }
    if (tcpServer_.isListening()) {
        qDebug() << "Server started on port" << port;
    } else {
        qDebug() << "Failed to start server:" << tcpServer_.errorString();
    }
}

Server::~Server() {
    // 服务器停止时，关闭所有连接
    stop();
}

void Server::start() {
    // 服务器启动时，可以添加一些额外的配置

    qDebug() << "Server started with additional configurations.";
}

void Server::stop() {
            foreach (Connection* connection, connections_) {
            delete connection;
        }
    connections_.clear();
    tcpServer_.close();
    qDebug() << "Server stopped.";
}

void Server::acceptConnection() {
    QTcpSocket* socket = tcpServer_.nextPendingConnection();
    Connection* connection = new Connection(socket, this);
    connections_.insert(connection);
}
