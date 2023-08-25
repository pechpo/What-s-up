#include "connection.h"
#include <QDebug>

Connection::Connection() {
    connected = false;
    connect(this, SIGNAL(readyRead()),this, SLOT(receiveMessage()));
}
Connection::~Connection() {
    disconnectFromHost();
}

void Connection::connectServer(const QString& IP, quint16 port) {
    // todo: more detailed validity check
    if (port > 0) {
        serverPort = port;
    }
    if (IP.length() > 0) {
        serverIP = IP;
    }
    connectToHost(QHostAddress(serverIP), serverPort);
    qDebug() << "connection " << serverIP << ":" << serverPort;
}

bool Connection::isConnected() {
    if (false == connected) {
        connected = waitForConnected();
    }
    return connected;
}

void Connection::receiveMessage() {
    // todo
    QByteArray info = readAll();
    qDebug() << "received message: " + info;
}

void Connection::sendMessage(const QString &text) {
    // called only if isConnected()
    waitForBytesWritten();
    write(text.toStdString().c_str());
    qDebug() << "send " << text;
}
