//
// Created by zixin on 23-8-25.
//

#ifndef DATABASE_MESSAGE_H
#define DATABASE_MESSAGE_H

#include "QString"

class Message {
public:
    Message();

    Message(const quint32 &new_ID, const quint32 &new_sender_ID, const quint32 &new_receiver_ID, const QString &new_content,
            const QString &new_time);

    ~Message();

    quint32 getID() const;

    quint32 getSenderID() const;

    quint32 getReceiverID() const;

    QString getContent() const;

    QString getTime() const;

    void setID(const quint32 &new_ID);

    void setSenderID(const quint32 &new_sender_ID);

    void setReceiverID(const quint32 &new_receiver_ID);

    void setContent(const QString &new_content);

    void setTime(const QString &new_time);

    quint32 ID;

    quint32 sender_ID;

    quint32 receiver_ID;

    QString content;

    QString time;

private:
    static int message_id;
};

#endif //DATABASE_MESSAGE_H