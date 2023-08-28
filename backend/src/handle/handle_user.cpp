//
// Created by zixin on 23-8-27.
//

// src/handle/handle_user.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

QJsonObject Handle::ins_usr(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString username = obj["username"].toString();
    QString password = obj["password"].toString();
    QString email = obj["email"].toString();
    QString avatar = obj["avatar"].toString();
    DB *db = DB::get_instance();
    auto flag = db->ins_usr(User(id, username, password, email, avatar));

    QJsonObject response;
    response["type"] = "r_register";
    response["success"] = flag;
    return response;
}

QJsonObject Handle::ck_login(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString password = obj["password"].toString();
    DB *db = DB::get_instance();
    auto flag = db->ck_login(id, password);

    QJsonObject response;
    response["type"] = "r_login";
    response["success"] = flag;  // set to false if login fails
    // Send the response back to client
}

QJsonObject Handle::qry_usr(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_usr(id);

    QJsonObject response;
    response["type"] = "r_myInfo";
    response["success"] = true;  // set to false if query fails
    response["id"] = QJsonValue((int) flag.getID());
    response["username"] = flag.getName();
    response["password"] = flag.getPwd();
    response["email"] = flag.getEmail();
    response["avatar"] = flag.getAvatarName();
    // Send the response back to client
}

QJsonObject Handle::upd_usr_name(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString username = obj["username"].toString();
    DB *db = DB::get_instance();
    auto flag = db->upd_usr_name(id, username);

    QJsonObject response;
    response["type"] = "r_upd_usr_name";
    response["success"] = flag;  // set to false if update fails
    // Send the response back to client
}

QJsonObject Handle::upd_usr_password(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString password = obj["password"].toString();
    DB *db = DB::get_instance();
    auto flag = db->upd_usr_password(id, password);

    QJsonObject response;
    response["type"] = "r_upd_usr_password";
    response["success"] = flag;  // set to false if update fails
    // Send the response back to client
}

QJsonObject Handle::upd_usr_avatar(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString avatar = obj["avatar"].toString();
    DB *db = DB::get_instance();
    auto flag = db->upd_usr_avatar(id, avatar);

    QJsonObject response;
    response["type"] = "r_upd_usr_avatar";
    response["success"] = flag;  // set to false if update fails
    // Send the response back to client
}

QJsonObject Handle::upd_usr_email(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString email = obj["email"].toString();
    DB *db = DB::get_instance();
    auto flag = db->upd_usr_email(id, email);

    QJsonObject response;
    response["type"] = "r_upd_usr_email";
    response["success"] = flag;  // set to false if update fails
    // Send the response back to client
}

QJsonObject Handle::del_usr(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->del_usr(id);

    QJsonObject response;
    response["type"] = "r_del_usr";
    response["success"] = flag;  // set to false if deletion fails
    // Send the response back to client
}
