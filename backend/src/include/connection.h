//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_CONNECTION_H
#define WHAT_S_UP_CONNECTION_H

#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QQueue>

class Connection : public QObject {
Q_OBJECT

public:
    explicit Connection(QTcpSocket* socket, QObject* parent = nullptr);
    ~Connection();

    void send(const QString& message); // 发送消息

signals:
    void messageReceived(const QString& message); // 消息接收信号

private slots:
    void readMessage(); // 读取消息
    void writeMessage(); // 异步写入消息

private:
    QTcpSocket* socket_; // TCP 套接字
    QQueue<QString> write_messages_; // 待发送的消息队列
};

#endif // WHAT_S_UP_CONNECTION_H
