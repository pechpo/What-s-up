#include "group.h"

quint32 Group::getID() const {
    return ID;
}

QString Group::getName() const {
    return name;
}

QString Group::getAvatarName() const {
    return ava;
}

void Group::setID(const quint32 &new_ID) {
    this->ID = new_ID;
}

void Group::setName(const QString &new_name) {
    this->name = new_name;
}

void Group::setAvatarName(const QString &new_ava) {
    this->ava = new_ava;
}