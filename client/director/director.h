#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <QObject>

class Director : public QObject
{
    Q_OBJECT
public:
    explicit Director(QObject *parent = nullptr);
    static Director* getInstance();
    ~Director();
signals:

private:
    static Director* self;

};

#endif // DIRECTOR_H
