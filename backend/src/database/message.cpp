#include "message.h"

int Message::message_id = 0;

quint32 Message::getID() const {
    return ID;
}

quint32 Message::getSenderID() const {
    return sender_ID;
}

quint32 Message::getReceiverID() const {
    return receiver_ID;
}

QString Message::getContent() const {
    return content;
}

QString Message::getTime() const {
    return time;
}

void Message::setID(const quint32 &new_ID) {
    this->ID = new_ID;
}

void Message::setSenderID(const quint32 &new_sender_ID) {
    this->sender_ID = new_sender_ID;
}

void Message::setReceiverID(const quint32 &new_receiver_ID) {
    this->receiver_ID = new_receiver_ID;
}

void Message::setContent(const QString &new_content) {
    this->content = new_content;
}

void Message::setTime(const QString &new_time) {
    this->time = new_time;
}

Message::Message() {
    this->ID = 0;
    this->sender_ID = 0;
    this->receiver_ID = 0;
    this->content = "";
    this->time = "";
}

Message::Message(const quint32 &new_ID, const quint32 &new_sender_ID, const quint32 &new_receiver_ID,
                 const QString &new_content, const QString &new_time) {
    this->ID = new_ID;
    this->sender_ID = new_sender_ID;
    this->receiver_ID = new_receiver_ID;
    this->content = new_content;
    this->time = new_time;
}

Message::~Message() = default;