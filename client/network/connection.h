#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    Connection();
    ~Connection();
    void connectServer(const QString &IP = "", quint16 port = 0);

public slots:
    void receiveMessage();
    void sendMessage(const QJsonObject&); // use JSON
    bool isConnected();

private:
    QString serverIP;
    quint16 serverPort;
    bool connected;
    quint32 curRemainSize;
};

#endif // CONNECTION_H
