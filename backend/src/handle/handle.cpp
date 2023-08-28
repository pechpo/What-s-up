//
// Created by zixin on 23-8-27.
//

// src/handle/handle.cpp

#include <QJsonObject>
#include "handle.h"
#include "db.h"

Handle* Handle::hd = nullptr;

Handle::Handle() {
    handlemap["e_register"] = [this](auto && PH1) { return e_register(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_login"] = [this](auto && PH1) { return q_login(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_editInfo"] = [this](auto && PH1) { return e_editInfo(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_myInfo"] = [this](auto && PH1) { return q_myInfo(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_userInfo"] = [this](auto && PH1) { return q_userInfo(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_send"] = [this](auto && PH1) { return e_send(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_chatHistory"] = [this](auto && PH1) { return q_chatHistory(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_list_myChats"] = [this](auto && PH1) { return q_list_myChats(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_list_usersInChat"] = [this](auto && PH1) { return q_list_usersInChat(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_addFriend"] = [this](auto && PH1) { return e_addFriend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_list_friendRequests"] = [this](auto && PH1) { return q_list_friendRequests(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_list_myFriends"] = [this](auto && PH1) { return q_list_myFriends(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_acceptFriend"] = [this](auto && PH1) { return e_acceptFriend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_createChat"] = [this](auto && PH1) { return e_createChat(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_joinChat"] = [this](auto && PH1) { return e_joinChat(std::forward<decltype(PH1)>(PH1)); };
    handlemap["q_list_filesInChat"] = [this](auto && PH1) { return q_list_filesInChat(std::forward<decltype(PH1)>(PH1)); };
}

Handle::~Handle() {
    delete hd;
}

QJsonObject Handle::handle(const QJsonObject &json) {
    return handlemap[json["type"].toString()](json);
}

Handle * Handle::get_instance() {
    if (hd == nullptr) {
        hd = new Handle;
    }
    return hd;
}

bool Handle::check(const int &id, const int &group) {
    DB *db = DB::get_instance();
    return db->check(id, group);
}