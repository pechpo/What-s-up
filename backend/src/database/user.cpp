#include "user.h"

quint32 User::getID() const {
    return ID;
}

QString User::getName() const {
    return name;
}

QString User::getPwd() const {
    return pwd;
}

QString User::getAvatarName() const {
    return ava;
}

QString User::getEmail() const {
    return ema;
}

void User::setID(const quint32 &new_ID) {
    this->ID = new_ID;
}

void User::setName(const QString &new_name) {
    this->name = new_name;
}

void User::setPwd(const QString &new_pwd) {
    this->pwd = new_pwd;
}

void User::setAvatarName(const QString &new_ava) {
    this->ava = new_ava;
}

void User::setEmail(const QString &new_ema) {
    this->ema = new_ema;
}

User::User() {
    this->ID = 0;
    this->name = "";
    this->pwd = "";
    this->ava = "";
    this->ema = "";
}

