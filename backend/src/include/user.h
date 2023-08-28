//
// Created by zixin on 23-8-25.
//

#ifndef DATABASE_USER_H
#define DATABASE_USER_H

#include "QString"
class User {
public:
    User();

    User(const quint32 &new_ID, const QString &new_name, const QString &new_pwd, const QString &new_ava, const QString &new_ema);

    ~User();

    quint32 getID() const;

    QString getName() const;

    QString getPwd() const;

    QString getAvatarName() const;

    QString getEmail() const;

    void setID(const quint32 &new_ID);

    void setName(const QString &new_name);

    void setPwd(const QString &new_pwd);

    void setAvatarName(const QString &new_ava);

    void setEmail(const QString &new_ema);

    quint32 ID;

    QString name;

    QString pwd;

    QString ava;

    QString ema;

private:
    static int user_id;
};

#endif //DATABASE_USER_H