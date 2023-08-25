#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <QObject>

#include "network/connection.h"

class Director : public QObject
{
    Q_OBJECT
public:
    explicit Director(QObject *parent = nullptr);
    ~Director();
    static Director* getInstance();
    void connectServer(const QString& , quint16);
signals:

private:
    static Director* self;
    static Connection* conn;
    static Connection* getConnection();
};

#endif // DIRECTOR_H
