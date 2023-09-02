//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_CONNECTION_H
#define WHAT_S_UP_CONNECTION_H

#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QQueue>
#include <QByteArray>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

class Connection : public QTcpSocket {
Q_OBJECT

public:
    int id = 0;

    explicit Connection(qintptr);
    ~Connection();

    void receiveMessage(); // 读取消息
    void sendMessage(const QJsonObject &obj); // 异步写入消息

signals:
    void messageReceived(const QString& message); // 消息接收信号

private:
    QTcpSocket* socket_; // TCP 套接字
    QQueue<QString> write_messages_; // 待发送的消息队列

    int curRemainSize = 0;

    void handleReceivedMessage(const QString &message);

};

#endif // WHAT_S_UP_CONNECTION_H