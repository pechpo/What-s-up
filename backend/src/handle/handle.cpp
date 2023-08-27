//
// Created by zixin on 23-8-27.
//

// src/handle/handle.cpp

#include <QJsonObject>
#include "handle.h"

Handle::Handle() {
    handlemap["e_register"] = [this](auto &&PH1) { ins_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_login"] = [this](auto &&PH1) { ck_login(std::forward<decltype(PH1)>(PH1)); };
    handlemap["e_myInfo"] = [this](auto &&PH1) { qry_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_name"] = [this](auto &&PH1) { upd_usr_name(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_password"] = [this](auto &&PH1) { upd_usr_password(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_avatar"] = [this](auto &&PH1) { upd_usr_avatar(std::forward<decltype(PH1)>(PH1)); };
    handlemap["upd_usr_email"] = [this](auto &&PH1) { upd_usr_email(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_usr"] = [this](auto &&PH1) { del_usr(std::forward<decltype(PH1)>(PH1)); };
    handlemap["add_friend"] = [this](auto &&PH1) { add_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_friend"] = [this](auto &&PH1) { del_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["create_group"] = [this](auto &&PH1) { create_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["add_group_member"] = [this](auto &&PH1) { add_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_group_member"] = [this](auto &&PH1) { del_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["del_group"] = [this](auto &&PH1) { del_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["ins_message"] = [this](auto &&PH1) { ins_message(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_pri"] = [this](auto &&PH1) { qry_pri(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_friend"] = [this](auto &&PH1) { qry_friend(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_group"] = [this](auto &&PH1) { qry_group(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_group_member"] = [this](auto &&PH1) { qry_group_member(std::forward<decltype(PH1)>(PH1)); };
    handlemap["qry_message"] = [this](auto &&PH1) { qry_message(std::forward<decltype(PH1)>(PH1)); };
}
