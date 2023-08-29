//
// Created by zixin on 23-8-27.
//

// src/handle/handle.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

Handle *Handle::hd = nullptr;

Handle::Handle() {
    handlemap["e_register"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_register(PH1, PH2);
    };
    handlemap["q_login"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_login(PH1, PH2);
    };
    handlemap["q_myInfo"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_myInfo(PH1, PH2);
    };
    handlemap["q_userInfo"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_userInfo(PH1, PH2);
    };
    handlemap["e_editInfo"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_editInfo(PH1, PH2);
    };
    handlemap["q_list_myChats"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_list_myChats(PH1, PH2);
    };
    handlemap["q_chatHistory"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_chatHistory(PH1, PH2);
    };
    handlemap["e_send"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_send(PH1, PH2);
    };
    handlemap["q_list_usersInChat"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_list_usersInChat(PH1, PH2);
    };
    handlemap["e_addFriend"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_addFriend(PH1, PH2);
    };
    handlemap["q_list_friendRequests"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_list_friendRequests(PH1, PH2);
    };
    handlemap["q_list_myFriends"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_list_myFriends(PH1, PH2);
    };
    handlemap["e_acceptFriend"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_acceptFriend(PH1, PH2);
    };
    handlemap["e_createChat"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_createChat(PH1, PH2);
    };
    handlemap["e_joinChat"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_joinChat(PH1, PH2);
    };
    handlemap["q_list_filesInChat"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_list_filesInChat(PH1, PH2);
    };
    handlemap["e_updateFile"] = [this](auto &&PH1, auto &&PH2) {
        return this->e_updateFile(PH1, PH2);
    };
    handlemap["q_downloadFile"] = [this](auto &&PH1, auto &&PH2) {
        return this->q_downloadFile(PH1, PH2);
    };
}

Handle::~Handle() {
    delete hd;
}

QJsonObject Handle::handle(const int &id, const QJsonObject &json) {
    return handlemap[json["type"].toString()](id, json);
}

Handle *Handle::get_instance() {
    if (hd == nullptr) {
        hd = new Handle;
    }
    return hd;
}

bool Handle::check(const int &id, const int &group) {
    DB *db = DB::get_instance();
    return db->check(id, group);
}