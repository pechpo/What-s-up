#include "chat.h"

quint32 chat::getID() const {
    return ID;
}

QString chat::getName() const {
    return name;
}

QString chat::getAvatarName() const {
    return ava;
}

void chat::setID(const quint32 &new_ID) {
    this->ID = new_ID;
}

void chat::setName(const QString &new_name) {
    this->name = new_name;
}

void chat::setAvatarName(const QString &new_ava) {
    this->ava = new_ava;
}

chat::chat() {
    this->ID = 0;
    this->name = "";
    this->ava = "";
}

chat::chat(const quint32 &new_ID, const QString &new_name, const QString &new_ava) {
    this->ID = new_ID;
    this->name = new_name;
    this->ava = new_ava;
}

chat::~chat() = default;