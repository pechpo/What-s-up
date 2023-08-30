//
// Created by zixin on 23-8-25.
//

#ifndef DATABASE_MESSAGE_H
#define DATABASE_MESSAGE_H

#include "QString"

class Message {
public:
    Message();

    Message(const quint32 &new_ID, const quint32 &new_sender_ID, const quint32 &new_receiver_ID,
            const QString &new_content,
            const QString &new_time, const QString &new_sender_name, const bool &new_is_file,
            const QString &new_file_name, const QString &new_type);

    ~Message();

    quint32 getID() const;

    quint32 getSenderID() const;

    quint32 getReceiverID() const;

    QString getContent() const;

    QString getTime() const;

    QString getSenderName() const;

    bool getIsFile() const;

    QString getFileName() const;

    QString getFormat() const;

    void setID(const quint32 &new_ID);

    void setSenderID(const quint32 &new_sender_ID);

    void setReceiverID(const quint32 &new_receiver_ID);

    void setContent(const QString &new_content);

    void setTime(const QString &new_time);

    void setSenderName(const QString &new_sender_name);

    void setIsFile(const bool &new_is_file);

    void setFileName(const QString &new_file_name);

    void setFormat(const QString &new_format);

private:
    quint32 ID;

    quint32 sender_ID;

    quint32 receiver_ID;

    QString content;

    QString time;

    QString sender_name;

    bool is_file;

    QString file_name;

    QString format;
};

#endif //DATABASE_MESSAGE_H