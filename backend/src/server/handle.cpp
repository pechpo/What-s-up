//
// Created by zixin on 23-8-27.
//

// src/server/handle.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

Handle::Handle() {
    handlemap["ins_usr"] = [this](auto &&PH1) { ins_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_name"] = [this](auto &&PH1) { upd_usr_name(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_password"] = [this](auto &&PH1) { upd_usr_password(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_avatar"] = [this](auto &&PH1) { upd_usr_avatar(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_email"] = [this](auto &&PH1) { upd_usr_email(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_usr"] = [this](auto &&PH1) { del_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["add_friend"] = [this](auto &&PH1) { add_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_friend"] = [this](auto &&PH1) { del_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["create_group"] = [this](auto &&PH1) { create_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["add_group_member"] = [this](auto &&PH1) { add_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_group_member"] = [this](auto &&PH1) { del_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_group"] = [this](auto &&PH1) { del_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["ins_message"] = [this](auto &&PH1) { ins_message(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_pri"] = [this](auto &&PH1) { qry_pri(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_usr"] = [this](auto &&PH1) { qry_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_friend"] = [this](auto &&PH1) { qry_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_group"] = [this](auto &&PH1) { qry_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_group_member"] = [this](auto &&PH1) { qry_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_message"] = [this](auto &&PH1) { qry_message(std::forward<decltype(PH1)>(PH1)); };
}

void Handle::ins_usr(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString username = obj["username"].toString();
    QString password = obj["password"].toString();
    QString email = obj["email"].toString();
    QString avater = obj["avater"].toString();
    DB *db = DB::get_instance();
    auto flag = db->ins_usr(User(id, username, password, email, avater));

    QJsonObject response;
    response["type"] = "r_register";
    response["success"] = flag;  // set to false if registration fails
    // Send the response back to client
}

void Handle::upd_usr_name(const QJsonObject &obj) {
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

void Handle::upd_usr_password(const QJsonObject &obj) {
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

void Handle::upd_usr_avatar(const QJsonObject &obj) {
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

void Handle::upd_usr_email(const QJsonObject &obj) {
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

void Handle::del_usr(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->del_usr(id);

    QJsonObject response;
    response["type"] = "r_del_usr";
    response["success"] = flag;  // set to false if deletion fails
    // Send the response back to client
}

void Handle::add_friend(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id1 = obj["id1"].toInt();
    quint32 id2 = obj["id2"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->add_friend(id1, id2);

    QJsonObject response;
    response["type"] = "r_add_friend";
    response["success"] = flag;  // set to false if addition fails
    // Send the response back to client
}

void Handle::del_friend(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id1 = obj["id1"].toInt();
    quint32 id2 = obj["id2"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->del_friend(id1, id2);

    QJsonObject response;
    response["type"] = "r_del_friend";
    response["success"] = flag;  // set to false if deletion fails
    // Send the response back to client
}

void Handle::create_group(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    QString name = obj["name"].toString();
    QString avatar = obj["avatar"].toString();
    DB *db = DB::get_instance();
    auto flag = db->create_group(Group(id, name, avatar));

    QJsonObject response;
    response["type"] = "r_create_group";
    response["success"] = flag;  // set to false if creation fails
    // Send the response back to client
}

void Handle::add_group_member(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 group_id = obj["group_id"].toInt();
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->add_group_member(group_id, id);

    QJsonObject response;
    response["type"] = "r_add_group_member";
    response["success"] = flag;  // set to false if addition fails
    // Send the response back to client
}

void Handle::del_group_member(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 group_id = obj["group_id"].toInt();
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->del_group_member(group_id, id);

    QJsonObject response;
    response["type"] = "r_del_group_member";
    response["success"] = flag;  // set to false if deletion fails
    // Send the response back to client
}

void Handle::del_group(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 group_id = obj["group_id"].toInt();
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->del_group(group_id, id);

    QJsonObject response;
    response["type"] = "r_del_group";
    response["success"] = flag;  // set to false if deletion fails
    // Send the response back to client
}

void Handle::ins_message(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    quint32 group_id = obj["group_id"].toInt();
    QString time = obj["time"].toString();
    QString content = obj["content"].toString();
    quint32 sender_id = obj["sender_id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->ins_message(Message(id, sender_id, group_id, content, time));

    QJsonObject response;
    response["type"] = "r_ins_message";
    response["success"] = flag;  // set to false if insertion fails
    // Send the response back to client
}

void Handle::qry_pri(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    quint32 group_id = obj["group_id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_pri(id, group_id);

    QJsonObject response;
    response["type"] = "r_qry_pri";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

void Handle::qry_usr(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_usr(id);

    QJsonObject response;
    response["type"] = "r_qry_usr";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

void Handle::qry_friend(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id1 = obj["id1"].toInt();
    quint32 id2 = obj["id2"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_friend(id1, id2);

    QJsonObject response;
    response["type"] = "r_qry_friend";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

void Handle::qry_group(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 group_id = obj["group_id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_group(group_id);

    QJsonObject response;
    response["type"] = "r_qry_group";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

void Handle::qry_group_member(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 group_id = obj["group_id"].toInt();
    quint32 id = obj["id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_group_member(group_id, id);

    QJsonObject response;
    response["type"] = "r_qry_group_member";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

void Handle::qry_message(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 id = obj["id"].toInt();
    quint32 group_id = obj["group_id"].toInt();
    QString time = obj["time"].toString();
    QString content = obj["content"].toString();
    quint32 sender_id = obj["sender_id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_message(id, group_id, time, content, sender_id);

    QJsonObject response;
    response["type"] = "r_qry_message";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}
