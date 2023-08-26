#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <QObject>
#include <QJsonObject>

#include "network/connection.h"

class Director : public QObject
{
    Q_OBJECT

public:
    explicit Director(QObject *parent = nullptr);
    ~Director();
    static Director* getInstance();
    void act(const QJsonObject&); // deal with received JSON message
    void connectServer(const QString& , quint16);
    void sendPureMessage(const QString&);

signals:
    // todo

private:
    static Director* self;
    static Connection* conn;
    static Connection* getConnection();
};

#endif // DIRECTOR_H
