#include "db.h"
#include <QSqlQuery>

//user id, name, password, avatar, email
//message id, chat_id, sender_id, content, time
//chat id, name, avatar


DB* DB::db = nullptr;

DB::DB() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./src/database/data.db");
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
    delete db;
}

bool DB::e_register(const User &user) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO user (id, name, password, avatar, email) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(user.getID());
    query.addBindValue(user.getName());
    query.addBindValue(user.getPwd());
    query.addBindValue(user.getAvatarName());
    query.addBindValue(user.getEmail());
    return query.exec();
}

bool DB::q_login(const quint32 &ID, const QString &password) {
    QSqlQuery query(database);
    query.prepare("SELECT password FROM user WHERE id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        return query.value(0).toString() == password;
    }
    return false;
}

bool DB::e_editInfo(const User &user) {
    QSqlQuery query(database);
    query.prepare("UPDATE user SET name = ?, password = ?, avatar = ?, email = ? WHERE id = ?");
    query.addBindValue(user.getName());
    query.addBindValue(user.getPwd());
    query.addBindValue(user.getAvatarName());
    query.addBindValue(user.getEmail());
    query.addBindValue(user.getID());
    return query.exec();
}

User DB::q_myInfo(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user WHERE id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        User user;
        user.setID(query.value(0).toUInt());
        user.setName(query.value(1).toString());
        user.setPwd(query.value(2).toString());
        user.setAvatarName(query.value(3).toString());
        user.setEmail(query.value(4).toString());
        return user;
    }
    return User();
}

User DB::q_userInfo(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user WHERE id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        User user;
        user.setID(query.value(0).toUInt());
        user.setName(query.value(1).toString());
        user.setPwd(query.value(2).toString());
        user.setAvatarName(query.value(3).toString());
        user.setEmail(query.value(4).toString());
        return user;
    }
    return {};
}

bool DB::e_createChat(const quint32 &ID, const QString &name, const QString &avatarName) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO chat (id, name, avatar) VALUES (?, ?, ?)");
    query.addBindValue(2);
    query.addBindValue(name);
    query.addBindValue(avatarName);
    if (!query.exec()) {
        return false;
    }
    query.clear();
    query.prepare("INSERT INTO user_chat (user_id, chat_id) VALUES (?, ?)");
    query.addBindValue(ID);
    query.addBindValue(1);
    return query.exec();
}

bool DB::e_joinChat(const quint32 &ID, const quint32 &chat_ID) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO user_chat (user_id, chat_id) VALUES (?, ?)");
    query.addBindValue(ID);
    query.addBindValue(chat_ID);
    return query.exec();
}

bool DB::e_quitChat(const quint32 &ID, const quint32 &chat_ID) {
    QSqlQuery query(database);
    query.prepare("DELETE FROM user_chat WHERE user_id = ? AND chat_id = ?");
    query.addBindValue(ID);
    query.addBindValue(chat_ID);
    return query.exec();
}

bool DB::e_delChat(const quint32 &ID, const quint32 &chat_ID) {
    QSqlQuery query(database);
    query.prepare("DELETE FROM chat WHERE id = ?");
    query.addBindValue(chat_ID);
    return query.exec();
}

QList<Group> DB::q_list_myChats(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT chat_id FROM user_chat WHERE user_id = ?");
    query.addBindValue(ID);
    query.exec();
    QList<Group> chats;
    while (query.next()) {
        Group chat;
        chat.setID(query.value(0).toUInt());
        chats.append(chat);
    }
    return chats;
}

QList<User> DB::q_list_usersInChat(const quint32 &chat_ID) {
    QSqlQuery query(database);
    query.prepare("SELECT user_id FROM user_chat WHERE chat_id = ?");
    query.addBindValue(chat_ID);
    query.exec();
    QList<User> users;
    while (query.next()) {
        User user;
        user.setID(query.value(0).toUInt());
        users.append(user);
    }
    return users;
}

bool DB::e_addFriend(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO friend_request (user_id, friend_id) VALUES (?, ?)");
    query.addBindValue(ID);
    query.addBindValue(ID);
    return query.exec();
}

QList<User> DB::q_list_friendRequests(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT friend_id FROM friend_request WHERE user_id = ?");
    query.addBindValue(ID);
    query.exec();
    QList<User> users;
    while (query.next()) {
        User user;
        user.setID(query.value(0).toUInt());
        users.append(user);
    }
    return users;
}

QList<User> DB::q_list_myFriends(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT friend_id FROM friend WHERE user_id = ?");
    query.addBindValue(ID);
    query.exec();
    QList<User> users;
    while (query.next()) {
        User user;
        user.setID(query.value(0).toUInt());
        users.append(user);
    }
    return users;
}

bool DB::e_acceptFriend(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO friend (user_id, friend_id) VALUES (?, ?)");
    query.addBindValue(ID);
    query.addBindValue(ID);
    return query.exec();
}

bool DB::e_send(const Message &message) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO message (id, chat_id, sender_id, content, time) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(message.getID());
    query.addBindValue(message.getReceiverID());
    query.addBindValue(message.getSenderID());
    query.addBindValue(message.getContent());
    query.addBindValue(message.getTime());
    return query.exec();
}

QList<Message> DB::q_chatHistory(const quint32 &chat_ID, const quint32 &time, const quint32 &count) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM message WHERE chat_id = ? AND time < ? ORDER BY time DESC LIMIT ?");
    query.addBindValue(chat_ID);
    query.addBindValue(time);
    query.addBindValue(count);
    query.exec();
    QList<Message> messages;
    while (query.next()) {
        Message message;
        message.setID(query.value(0).toUInt());
        message.setReceiverID(query.value(1).toUInt());
        message.setSenderID(query.value(2).toUInt());
        message.setContent(query.value(3).toString());
        message.setTime(query.value(4).toString());
        messages.append(message);
    }
    return messages;
}

QList<Message> DB::q_list_filesInChat(const quint32 &chat_ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM message WHERE chat_id = ? AND content IS NULL");
    query.addBindValue(chat_ID);
    query.exec();
    QList<Message> messages;
    while (query.next()) {
        Message message;
        message.setID(query.value(0).toUInt());
        message.setReceiverID(query.value(1).toUInt());
        message.setSenderID(query.value(2).toUInt());
        message.setContent(query.value(3).toString());
        message.setTime(query.value(4).toString());
        messages.append(message);
    }
    return messages;
}

bool DB::check(const int &id, const int &group) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user_chat WHERE user_id = ? AND chat_id = ?");
    query.addBindValue(id);
    query.addBindValue(group);
    query.exec();
    if (query.next())return true;
    return false;
}

DB * DB::get_instance() {
    if (db == nullptr) {
        db = new DB;
    }
    return db;
}