#include "connection.h"

connection::connection() {
    connect(this, SIGNAL(readyRead()),this, SLOT(readMessage()));
}
connection::~connection() {
    disconnectFromHost();
}

void connection::connectServer(const QString& IP, quint16 port) {
    // todo: more detailed validity check
    if (port > 0) {
        serverPort = port;
    }
    if (IP.length() > 0) {
        serverIP = IP;
    }
    connectToHost(QHostAddress(serverIP), serverPort);
}

void connection::readMessage() {

}
