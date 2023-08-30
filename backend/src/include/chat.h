//
// Created by zixin on 23-8-25.
//

#ifndef DATABASE_chat_H
#define DATABASE_chat_H

#include "QString"

class chat {
public:
    chat();

    chat(const quint32 &new_ID, const QString &new_name, const QString &new_ava);

    ~chat();

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

#endif //DATABASE_chat_H