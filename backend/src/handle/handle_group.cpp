//
// Created by zixin on 23-8-27.
//

// src/server/handle_group.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

QJsonObject Handle::qry_friend(const QJsonObject &obj) {
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

QJsonObject Handle::add_friend(const QJsonObject &obj) {
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

QJsonObject Handle::del_friend(const QJsonObject &obj) {
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

QJsonObject Handle::create_group(const QJsonObject &obj) {
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

QJsonObject Handle::add_group_member(const QJsonObject &obj) {
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

QJsonObject Handle::del_group_member(const QJsonObject &obj) {
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

QJsonObject Handle::del_group(const QJsonObject &obj) {
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

QJsonObject Handle::qry_pri(const QJsonObject &obj) {
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

QJsonObject Handle::qry_group(const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 group_id = obj["group_id"].toInt();
    DB *db = DB::get_instance();
    auto flag = db->qry_group(group_id);

    QJsonObject response;
    response["type"] = "r_qry_group";
    response["success"] = flag;  // set to false if query fails
    // Send the response back to client
}

QJsonObject Handle::qry_group_member(const QJsonObject &obj) {
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