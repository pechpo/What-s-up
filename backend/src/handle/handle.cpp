//
// Created by zixin on 23-8-27.
//

// src/handle/handle.cpp

#include <QJsonObject>
#include "handle.h"

Handle* Handle::hd = nullptr;

Handle::Handle() {
    handlemap["e_register"] = [this](auto && PH1) { return ins_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_login"] = [this](auto && PH1) { return ck_login(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_query_user"] = [this](auto && PH1) { return qry_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_update_user_name"] = [this](auto && PH1) { return upd_usr_name(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_update_user_password"] = [this](auto && PH1) { return upd_usr_password(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_update_user_avatar"] = [this](auto && PH1) { return upd_usr_avatar(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_update_user_email"] = [this](auto && PH1) { return upd_usr_email(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_delete_user"] = [this](auto && PH1) { return del_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_add_friend"] = [this](auto && PH1) { return add_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_delete_friend"] = [this](auto && PH1) { return del_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_create_group"] = [this](auto && PH1) { return create_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_add_group_member"] = [this](auto && PH1) { return add_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_delete_group_member"] = [this](auto && PH1) { return del_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_delete_group"] = [this](auto && PH1) { return del_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_insert_message"] = [this](auto && PH1) { return ins_message(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_query_privilege"] = [this](auto && PH1) { return qry_pri(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_query_friend"] = [this](auto && PH1) { return qry_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_query_group"] = [this](auto && PH1) { return qry_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_query_group_member"] = [this](auto && PH1) { return qry_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_query_message"] = [this](auto && PH1) { return qry_message(std::forward<decltype(PH1)>(PH1)); };
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