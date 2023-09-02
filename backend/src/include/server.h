//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_SERVER_H
#define WHAT_S_UP_SERVER_H

#include <QTcpServer>
#include <QObject>
#include "connection.h"

class TCP : public QTcpServer {
Q_OBJECT
    void incomingConnection ( qintptr socketDescriptor );
};

class Server : public QObject {
Q_OBJECT

public:
    Server(const QString& address, quint16 port, QObject* parent = nullptr);
    ~Server();

    bool start(); // 开始监听
    void stop();  // 停止服务器

    static Server * get_instance();

    QSet<Connection*> connections_; // 连接集合

private slots:
    void acceptConnection(); // 异步接受连接

public:
    TCP tcpServer_;

    static Server * sv;
};


#endif // WHAT_S_UP_SERVER_H