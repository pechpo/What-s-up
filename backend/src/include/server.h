//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_SERVER_H
#define WHAT_S_UP_SERVER_H

#include <QTcpServer>
#include <QObject>
#include "connection.h"

class Server : public QObject {
Q_OBJECT

public:
    Server(const QString& address, quint16 port, QObject* parent = nullptr);
    ~Server();

    void start(); // 开始监听
    void stop();  // 停止服务器

private slots:
    void acceptConnection(); // 异步接受连接

private:
    QTcpServer tcpServer_;
    QSet<Connection*> connections_; // 连接集合
};

#endif // WHAT_S_UP_SERVER_H
