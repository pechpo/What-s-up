#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class connection : public QTcpSocket
{
public:
    connection();
    ~connection();
    void connectServer(const QString &IP = "", quint16 port = 0);

public slots:
    void readMessage();

protected:
    QString serverIP;
    quint16 serverPort;

};

#endif // CONNECTION_H
