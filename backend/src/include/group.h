//
// Created by zixin on 23-8-25.
//

#ifndef DATABASE_GROUP_H
#define DATABASE_GROUP_H

#include "QString"

class Group {
public:
    Group();

    Group(const quint32 &new_ID, const QString &new_name, const QString &new_ava);

    ~Group();

    quint32 getID() const;

    QString getName() const;

    QString getAvatarName() const;

    void setID(const quint32 &new_ID);

    void setName(const QString &new_name);

    void setAvatarName(const QString &new_ava);

    quint32 ID;

    QString name;

    QString ava;
};

#endif //DATABASE_GROUP_H
