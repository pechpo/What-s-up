#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "user.h"
#include "message.h"
#include "group.h"

class DB {

public :
    DB();

    ~DB();

    bool ins_usr(const User& user);//新增用户

    bool ck_login(const quint32 &ID, const QString &pwd);//检查登录

    User qry_usr(const quint32 &ID);//查询用户

    bool upd_usr_name(const quint32 &ID, const QString &name);//修改用户名

    bool upd_usr_password(const quint32 &ID, const QString &pwd);//修改用户密码

    bool upd_usr_avatar(const quint32 &ID, const QString &ava);//修改用户头像

    bool upd_usr_email(const quint32 &ID, const QString &ema);//修改用户邮箱

    bool del_usr(const quint32 &ID);//删除用户

    bool add_friend(const quint32 &ID1, const quint32 &ID2);//添加好友

    bool del_friend(const quint32 &ID1, const quint32 &ID2);//删除好友

    bool create_group(const Group &gruop);//创建群组

    bool add_group_member(const quint32 &group_ID, const quint32 &ID);//添加群成员

    bool del_group_member(const quint32 &group_ID, const quint32 &ID);//踢除人出群组
    //群主解散群聊和自己退出群聊有区别，非管理员只能把自己踢除群聊，管理员可以解散群聊
    bool del_group(const quint32 &group_ID, const quint32 &ID);//解散群组

    bool ins_message(const Message &message);//插入消息

    bool qry_pri(const quint32 &ID, const quint32 &group_ID);//查询是否为群主

    bool qry_friend(const quint32 &ID1, const quint32 &ID2);//查询是否为好友

    bool qry_group(const quint32 &group_ID);//查询群组是否存在

    bool qry_group_member(const quint32 &group_ID, const quint32 &ID);//查询是否为群成员

    bool qry_message(const quint32 &ID);//查询消息是否存在

    bool qry_message(const quint32 &ID, const quint32 &group_ID);//查询消息是否存在

    bool qry_message(const quint32 &ID, const quint32 &group_ID, const QString &time);//查询消息是否存在

    bool qry_message(const quint32 &ID, const quint32 &group_ID, const QString &time, const QString &content);//查询消息是否存在

    bool qry_message(const quint32 &ID, const quint32 &group_ID, const QString &time, const QString &content, const quint32 &sender_ID);//查询消息是否存在

    static DB * get_instance();

private:

    static DB * db;

    QSqlDatabase database;
};
#endif // MAINWINDOW_H
