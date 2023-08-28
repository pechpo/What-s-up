//
// Created by zixin on 23-8-27.
//

//src/handle/handle_message.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

QJsonObject Handle::ins_message(const QJsonObject &obj) {
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

QJsonObject Handle::qry_message(const QJsonObject &obj) {
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
