//
// Created by zixin on 23-8-27.
//

#ifndef BACKEND_HANDLE_H
#define BACKEND_HANDLE_H

#include <QObject>

class Handle : public QObject{
public:
    Handle();

    QJsonObject ins_usr(const QJsonObject &json);

    QJsonObject ck_login(const QJsonObject &json);

    QJsonObject qry_usr(const QJsonObject &json);

    QJsonObject upd_usr_name(const QJsonObject &json);

    QJsonObject upd_usr_password(const QJsonObject &json);

    QJsonObject upd_usr_avatar(const QJsonObject &json);

    QJsonObject upd_usr_email(const QJsonObject &json);

    QJsonObject del_usr(const QJsonObject &json);

    QJsonObject add_friend(const QJsonObject &json);

    QJsonObject del_friend(const QJsonObject &json);

    QJsonObject create_group(const QJsonObject &json);

    QJsonObject add_group_member(const QJsonObject &json);

    QJsonObject del_group_member(const QJsonObject &json);

    QJsonObject del_group(const QJsonObject &json);

    QJsonObject ins_message(const QJsonObject &json);

    QJsonObject qry_pri(const QJsonObject &json);

    QJsonObject qry_friend(const QJsonObject &json);

    QJsonObject qry_group(const QJsonObject &json);

    QJsonObject qry_group_member(const QJsonObject &json);

    QJsonObject qry_message(const QJsonObject &json);

    QJsonObject handle(const QJsonObject &json);

    std::map<QString, std::function<QJsonObject(const QJsonObject &)>> handlemap;

    static Handle * get_instance();

private:

    static Handle * hd;
};

#endif //BACKEND_HANDLE_H