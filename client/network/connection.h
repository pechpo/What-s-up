#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QJsonObject>

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    Connection();
    ~Connection();
    void connectServer(const QString &IP = "", quint16 port = 0);
    void sendMessage(const QJsonObject&); // use JSON
    bool isConnected();

private slots:
    void receiveMessage();
    void disconnectFlag();

private:
    QString serverIP;
    quint16 serverPort;
    bool connected;
    quint32 curRemainSize;
};

#endif // CONNECTION_H
