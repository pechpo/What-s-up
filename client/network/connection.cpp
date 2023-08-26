#include "connection.h"
#include "director/director.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include <QJsonParseError>

#include <QDebug>

Connection::Connection() {
    connected = false;
    curRemainSize = 0;
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
    waitForConnected();
    qDebug() << "connection " << serverIP << ":" << serverPort;
}

bool Connection::isConnected() {
    if (false == connected) {
        connected = waitForConnected(1000);
    }
    return connected;
}

void Connection::receiveMessage() {
    while (bytesAvailable() > 0) { // may read more than one message
        QDataStream in(this);
        in.setVersion(QDataStream::Qt_6_5);
        if (0 == curRemainSize) {
            if (bytesAvailable() >= sizeof(quint32)) {
                in >> curRemainSize;
            }
            else {
                return ;
            }
        }
        if (bytesAvailable() < curRemainSize) {
            return ; // wait to read full message
        }
        // read a JSON
        QByteArray jsonBytes;
        in >> jsonBytes;
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(jsonBytes, &err);
        // *todo: deal with err
        if (!doc.isObject()) {
            // *todo: not object
        }
        QJsonObject obj = doc.object();
        Director::getInstance()->act(obj);
        curRemainSize = 0;
    }
}

void Connection::sendMessage(const QJsonObject &obj) {
    // called only if isConnected()
    waitForBytesWritten();
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray outMsg;
    QDataStream out(&outMsg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint32(0) << doc.toJson();
    // quint32(0) is for size
    out.device()->seek(0);
    out << quint32(outMsg.size() - sizeof(quint32));
    write(outMsg);
    // is flush() necessary?
    // flush();
}
