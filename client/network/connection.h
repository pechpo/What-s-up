#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class connection : public QTcpSocket
{
public:
    connection();

public slots:
    void readMessage();

};

#endif // CONNECTION_H
