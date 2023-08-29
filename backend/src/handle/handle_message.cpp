//
// Created by zixin on 23-8-27.
//

//src/handle/handle_message.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

QJsonObject Handle::e_send(const int &ID, const QJsonObject &obj) {
    // Extract the necessary fields from obj
    quint32 chatId = obj["chatId"].toInt();
    qDebug() << "chatId: " << chatId;
    quint32 senderId = obj["senderId"].toInt();
    qDebug() << "senderId: " << senderId;
    auto message = obj["message"].toObject();
    qDebug() << "message: " << message;
    QString content = message["content"].toString();
    qDebug() << "content: " << content;
    DB *db = DB::get_instance();
    auto flag = db->e_send(Message(1, senderId, chatId, content, "111"));

    QJsonObject response;
    response["type"] = "r_send";
    response["success"] = flag;  // set to false if insertion fails
    if(!flag){
        response["error"] = "Send failed";
    }
    return response;
    // Send the response back to client
}