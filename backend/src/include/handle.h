//
// Created by zixin on 23-8-27.
//

#ifndef BACKEND_HANDLE_H
#define BACKEND_HANDLE_H

#include <QObject>

class Handle : public QObject{
public:
    Handle();

    void ins_usr(const QJsonObject &json);

    void ck_login(const QJsonObject &json);

    void qry_usr(const QJsonObject &json);

    void upd_usr_name(const QJsonObject &json);

    void upd_usr_password(const QJsonObject &json);

    void upd_usr_avatar(const QJsonObject &json);

    void upd_usr_email(const QJsonObject &json);

    void del_usr(const QJsonObject &json);

    void add_friend(const QJsonObject &json);

    void del_friend(const QJsonObject &json);

    void create_group(const QJsonObject &json);

    void add_group_member(const QJsonObject &json);

    void del_group_member(const QJsonObject &json);

    void del_group(const QJsonObject &json);

    void ins_message(const QJsonObject &json);

    void qry_pri(const QJsonObject &json);

    void qry_friend(const QJsonObject &json);

    void qry_group(const QJsonObject &json);

    void qry_group_member(const QJsonObject &json);

    void qry_message(const QJsonObject &json);

    std::map<QString, std::function<void(const QJsonObject &)>> handlemap;
};

#endif //BACKEND_HANDLE_H
