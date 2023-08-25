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
    if (tcpServer_.listen(QHostAddress(address), port)) {
        qDebug() << "Server started on port" << port;
    } else {
        qDebug() << "Failed to start server:" << tcpServer_.errorString();
    }
}

Server::~Server() {
    stop();
}

void Server::start() {
    //一些可能的操作
    // 加载配置文件
    // QString configPath = "path/to/config/file";
    // loadConfig(configPath);

    // 初始化数据库连接
    // initDatabaseConnection();

    // 启动其他服务或组件
    // startOtherServices();

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
