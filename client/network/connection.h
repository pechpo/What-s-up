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
    virtual void receiveMessage();

protected:
    QString serverIP;
    quint16 serverPort;

};

#endif // CONNECTION_H
