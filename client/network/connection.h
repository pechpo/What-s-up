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
    void sendMessage(const QString &text); // todo: design a message class
    bool isConnected();

private:
    QString serverIP;
    quint16 serverPort;
    bool connected;
};

#endif // CONNECTION_H
