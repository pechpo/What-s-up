#include "db.h"
#include <QSqlQuery>

DB::DB() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./data.db");
    database.setUserName("root");

    if (database.open()) {
        qDebug() << "Successfully connect database\n";
    }
    else {
        qDebug() << "Fail to connect database\n";
    }
}

DB::~DB() {
    if (database.isOpen()) {
        database.close();
    }
}

bool DB::ins_usr(const User &user) {
    QSqlQuery query;
    query.prepare("insert into UserInfo values(:ID, :Username, :Pwd, :Avatar, :Email)");
    query.bindValue(":Id", user.getID());
    query.bindValue(":Username", user.getName());
    query.bindValue(":pwd", user.getPwd());
    query.bindValue(":avatar", user.getAvatarName());
    query.bindValue(":email", user.getEmail());
    query.exec();
}

bool upd_usr_name(const quint32 &ID, const QString &name) {
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Username = :Username WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":Username", QVariant(name));
    query.exec();
}

bool upd_usr_password(const quint32 &ID, const QString &pwd) {
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Pwd = :Pwd WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":Pwd", QVariant(pwd));
    query.exec();
}

bool upd_usr_avatar(const quint32 &ID, const QString &ava) {
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Avatar = :Avatar WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":Avatar", QVariant(ava));
    query.exec();
}

bool upd_usr_email(const quint32 &ID, const QString &ema) {
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Email = :Email WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":Email", QVariant(ema));
    query.exec();
}

bool del_usr(const quint32 &ID) {
    QSqlQuery query;
    query.prepare("DELETE FROM UserInfo WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();
}

bool add_friend(const quint32 &ID1, const quint32 &ID2) {
    if (ID1 == ID2) {
//        qDebug << "Can not add self!\n";
        return false;
    }
    QSqlQuery query;

    query.prepare("select * from Friendship WHERE ID1 = :ID1, ID2 = :ID2");
    query.bindValue(":ID1", QVariant(ID1));
    query.bindValue(":ID2", QVariant(ID2));
    query.exec();

    if (query.next()) {
//        qDebug << "Being friends before!\n";
        return false;
    }
    
    query.clear();
    query.prepare("insert into Friendship values(:ID1,:ID2)");
    query.bindValue(":ID1", QVariant(ID1));
    query.bindValue(":ID2", QVariant(ID2));
    query.exec();

    query.clear();
    query.prepare("insert into Friendship values(:ID1,:ID2)");
    query.bindValue(":ID1", QVariant(ID2));
    query.bindValue(":ID2", QVariant(ID1));
    query.exec();
}

bool del_friend(const quint32 &ID1, const quint32 &ID2) {
    if (ID1 == ID2) {
//        qDebug << "Can not del self!\n";
        return false;
    }
    QSqlQuery query;

    query.prepare("select * from Friendship WHERE ID1 = :ID1, ID2 = :ID2");
    query.bindValue(":ID1", QVariant(ID1));
    query.bindValue(":ID2", QVariant(ID2));
    query.exec();

    if (!query.next()) {
//        qDebug << "Not being friends before!\n";
        return false;
    }
    
    query.clear();
    query.prepare("delete from Friendship where ID1 =:ID1 and ID2 =:ID2");
    query.bindValue(":ID1", QVariant(ID1));
    query.bindValue(":ID2", QVariant(ID2));
    query.exec();

    query.clear();
    query.prepare("delete from Friendship where ID1 =:ID1 and ID2 =:ID2");
    query.bindValue(":ID1", QVariant(ID2));
    query.bindValue(":ID2", QVariant(ID1));
    query.exec();
}


bool DB::create_group(const Group &group) {
    QSqlQuery query;

    // 创建一个以 group_ID 为名的表，记录组成员信息
    query.prepare("CREATE TABLE GroupMembers_" + QString::number(group.getID()) + " (ID INTEGER, is_leader INTEGER)");
    query.exec();

    // 创建一个以 group_ID 为名的表，记录组内消息
    query.prepare("CREATE TABLE GroupMessages_" + QString::number(group.getID()) + " (ID INTEGER, message TEXT)");
    query.exec();

    return true;
}

bool DB::add_group_member(const quint32 &group_ID, const quint32 &ID) {
    QSqlQuery query;

    // 插入 ID 和 is_leader 到组成员表
    query.prepare("INSERT INTO GroupMembers_" + QString::number(group_ID) + " VALUES (:ID, :is_leader)");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":is_leader", QVariant(0));
    query.exec();

    return true;
}

bool DB::del_group_member(const quint32 &group_ID, const quint32 &ID) {
    QSqlQuery query;

    // 从组成员表中删除指定 ID 的人
    query.prepare("DELETE FROM GroupMembers_" + QString::number(group_ID) + " WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();

    return true;
}

bool DB::del_group(const quint32 &group_ID, const quint32 &ID) {
    QSqlQuery query;

    // 删除组成员表和组消息表
    query.prepare("DROP TABLE GroupMembers_" + QString::number(group_ID));
    query.exec();

    query.clear();
    query.prepare("DROP TABLE GroupMessages_" + QString::number(group_ID));
    query.exec();

    return true;
}

bool DB::ins_message(const Message &message) {
    QSqlQuery query;

    // 插入消息到表
    query.prepare("INSERT INTO Messages (ID, sender_ID, receiver_ID, content, time) VALUES (:ID, :sender_ID, :receiver_ID, :content, :time)");
    query.bindValue(":ID", message.getID());
    query.bindValue(":sender_ID", message.getSenderID());
    query.bindValue(":receiver_ID", message.getReceiverID());
    query.bindValue(":content", message.getContent());
    query.bindValue(":time", message.getTime());
    query.exec();

    return true;
}

bool DB::qry_pri(const quint32 &ID, const quint32 &group_ID) {
    QSqlQuery query;

    // 查询 ID 在 group_ID 中的权限
    query.prepare("SELECT is_leader FROM GroupMembers_" + QString::number(group_ID) + " WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();

    if (query.next()) {
        return query.value(0).toBool();
    }

    return false;
}

bool DB::qry_usr(const quint32 &ID) {
    QSqlQuery query;

    // 查询用户 ID 是否存在
    query.prepare("SELECT * FROM UserInfo WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_friend(const quint32 &ID1, const quint32 &ID2) {
    QSqlQuery query;

    // 查询 ID1 和 ID2 是否为好友
    query.prepare("SELECT * FROM Friendship WHERE ID1 = :ID1 AND ID2 = :ID2");
    query.bindValue(":ID1", QVariant(ID1));
    query.bindValue(":ID2", QVariant(ID2));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_group(const quint32 &group_ID) {
    QSqlQuery query;

    // 查询 group_ID 是否存在
    query.prepare("SELECT * FROM GroupInfo WHERE ID = :ID");
    query.bindValue(":ID", QVariant(group_ID));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_group_member(const quint32 &group_ID, const quint32 &ID) {
    QSqlQuery query;

    // 查询 ID 是否为 group_ID 的成员
    query.prepare("SELECT * FROM GroupMembers_" + QString::number(group_ID) + " WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_message(const quint32 &ID) {
    QSqlQuery query;

    // 查询消息 ID 是否存在
    query.prepare("SELECT * FROM Messages WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_message(const quint32 &ID, const quint32 &group_ID) {
    QSqlQuery query;

    // 查询消息 ID 和 group_ID 是否存在
    query.prepare("SELECT * FROM GroupMessages_" + QString::number(group_ID) + " WHERE ID = :ID");
    query.bindValue(":ID", QVariant(ID));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_message(const quint32 &ID, const quint32 &group_ID, const QString &time) {
    QSqlQuery query;

    // 查询消息 ID 和 group_ID 和 time 是否存在
    query.prepare("SELECT * FROM GroupMessages_" + QString::number(group_ID) + " WHERE ID = :ID AND time = :time");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":time", QVariant(time));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_message(const quint32 &ID, const quint32 &group_ID, const QString &time, const QString &content) {
    QSqlQuery query;

    // 查询消息 ID 和 group_ID 和 time 和 content 是否存在
    query.prepare("SELECT * FROM GroupMessages_" + QString::number(group_ID) + " WHERE ID = :ID AND time = :time AND content = :content");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":time", QVariant(time));
    query.bindValue(":content", QVariant(content));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

bool DB::qry_message(const quint32 &ID, const quint32 &group_ID, const QString &time, const QString &content, const quint32 &sender_ID) {
    QSqlQuery query;

    // 查询消息 ID 和 group_ID 和 time 和 content 和 sender_ID 是否存在
    query.prepare("SELECT * FROM GroupMessages_" + QString::number(group_ID) + " WHERE ID = :ID AND time = :time AND content = :content AND sender_ID = :sender_ID");
    query.bindValue(":ID", QVariant(ID));
    query.bindValue(":time", QVariant(time));
    query.bindValue(":content", QVariant(content));
    query.bindValue(":sender_ID", QVariant(sender_ID));
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

