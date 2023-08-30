#include "message.h"

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

QString Message::getSenderName() const {
    return sender_name;
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

void Message::setSenderName(const QString &new_sender_name) {
    this->sender_name = new_sender_name;
}

bool Message::getIsFile() const {
    return is_file;
}

void Message::setIsFile(const bool &new_is_file) {
    this->is_file = new_is_file;
}

QString Message::getFileName() const {
    return file_name;
}

void Message::setFileName(const QString &new_file_name) {
    this->file_name = new_file_name;
}

QString Message::getFormat() const {
    return format;
}

void Message::setFormat(const QString &new_format) {
    this->format = new_format;
}

Message::Message() {
    this->ID = 0;
    this->sender_ID = 0;
    this->receiver_ID = 0;
    this->content = "";
    this->time = "";
    this->sender_name = "";
    this->is_file = false;
    this->file_name = "";
    this->format = "";
}

Message::Message(const quint32 &new_ID, const quint32 &new_sender_ID, const quint32 &new_receiver_ID,
                 const QString &new_content, const QString &new_time, const QString &new_sender_name,
                 const bool &new_is_file, const QString &new_file_name, const QString &new_format) {
    this->ID = new_ID;
    this->sender_ID = new_sender_ID;
    this->receiver_ID = new_receiver_ID;
    this->content = new_content;
    this->time = new_time;
    this->sender_name = new_sender_name;
    this->is_file = new_is_file;
    this->file_name = new_file_name;
    this->format = new_format;
}

Message::~Message() = default;