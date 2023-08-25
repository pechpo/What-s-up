#include "connection.h"
#include <QDebug>

Connection::Connection() {
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

void Connection::receiveMessage() {

}
