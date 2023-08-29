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
            const QString &new_time, const QString &new_sender_name, const bool &is_file);

    ~Message();

    quint32 getID() const;

    quint32 getSenderID() const;

    quint32 getReceiverID() const;

    QString getContent() const;

    QString getTime() const;

    QString getSenderName() const;

    QString getFileName() const;

    void setID(const quint32 &new_ID);

    void setSenderID(const quint32 &new_sender_ID);

    void setReceiverID(const quint32 &new_receiver_ID);

    void setContent(const QString &new_content);

    void setTime(const QString &new_time);

    void setSenderName(const QString &new_sender_name);

    void setFileName(const QString &new_file_name);

    quint32 ID;

    quint32 sender_ID;

    quint32 receiver_ID;

    QString content;

    QString time;

    QString sender_name;

    bool is_file;

    QString file_name;
};

#endif //DATABASE_MESSAGE_H