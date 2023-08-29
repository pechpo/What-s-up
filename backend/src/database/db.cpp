#include "db.h"
#include <QSqlQuery>

//user id, name, password, avatar, email
//message id, chat_id, sender_id, content, time, is_file, sender_name
//chat id, name, avatar
//friend_request user_id, friend_id
//friend user_id, friend_id


DB *DB::db = nullptr;

int DB::user_id = 0;

int DB::group_id = 1;

int DB::message_id = 0;

int DB::new_group_id() {
    return ++group_id;
}

int DB::new_message_id() {
    return ++message_id;
}

int DB::new_user_id() {
    return ++user_id;
}

DB::DB() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./src/database/data.db");
    database.setUserName("root");

    if (database.open()) {
        qDebug() << "Successfully connect database\n";
    } else {
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
    return {};
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
    query.addBindValue(new_group_id());
    query.addBindValue(name);
    query.addBindValue(avatarName);
    if (!query.exec()) {
        return false;
    }
    query.clear();
    query.prepare("INSERT INTO user_chat (user_id, chat_id) VALUES (?, ?)");
    query.addBindValue(ID);
    query.addBindValue(group_id);
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
        QSqlQuery Query(database);
        Query.prepare("SELECT * FROM chat WHERE id = ?");
        Query.addBindValue(query.value(0).toUInt());
        Query.exec();
        if (!Query.next())return {};
        chat.setID(Query.value(0).toUInt());
        chat.setName(Query.value(1).toString());
        chat.setAvatarName(Query.value(3).toString());
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
        QSqlQuery Query(database);
        Query.prepare("SELECT * FROM user WHERE id = ?");
        Query.addBindValue(query.value(0).toUInt());
        Query.exec();
        if (!Query.next())return {};
        user.setID(Query.value(0).toUInt());
        user.setName(Query.value(1).toString());
        user.setAvatarName(Query.value(3).toString());
        users.append(user);
    }
    return users;
}

bool DB::e_addFriend(const quint32 &id, const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO friend_request (user_id, friend_id) VALUES (?, ?)");
    query.addBindValue(id);
    query.addBindValue(ID);
    return query.exec();
}

QList<User> DB::q_list_friendRequests(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT user_id FROM friend_request WHERE friend_id = ?");
    query.addBindValue(ID);
    query.exec();
    QList<User> users;
    while (query.next()) {
        User user;
        QSqlQuery Query(database);
        Query.prepare("SELECT * FROM user WHERE id = ?");
        Query.addBindValue(query.value(0).toUInt());
        Query.exec();
        if (!Query.next())return {};
        user.setID(Query.value(0).toUInt());
        user.setName(Query.value(1).toString());
        user.setAvatarName(Query.value(3).toString());
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
        QSqlQuery Query(database);
        Query.prepare("SELECT * FROM user WHERE id = ?");
        Query.addBindValue(query.value(0).toUInt());
        Query.exec();
        if (!Query.next())return {};
        user.setID(Query.value(0).toUInt());
        user.setName(Query.value(1).toString());
        user.setAvatarName(Query.value(3).toString());
        users.append(user);
    }
    return users;
}

bool DB::e_acceptFriend(const quint32 &id, const quint32 &ID, const bool &fl) {
    QSqlQuery query(database);
    if (fl) {
        query.prepare("INSERT INTO friend (user_id, friend_id) VALUES (?, ?)");
        query.addBindValue(id);
        query.addBindValue(ID);
        query.exec();

        query.clear();
        query.prepare("INSERT INTO friend (user_id, friend_id) VALUES (?, ?)");
        query.addBindValue(ID);
        query.addBindValue(id);
        query.exec();
    }
    query.clear();
    query.prepare("DELETE FROM friend_request WHERE user_id = ? AND friend_id = ?");
    query.addBindValue(ID);
    query.addBindValue(id);
    return query.exec();
}

bool DB::e_send(const Message &message) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO message (id, chat_id, sender_id, content, time, is_file, sender_name) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(message.getID());
    query.addBindValue(message.getReceiverID());
    query.addBindValue(message.getSenderID());
    query.addBindValue(message.getContent());
    query.addBindValue(message.getTime());
    query.addBindValue(message.is_file);
    query.addBindValue(message.getSenderName());
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
    query.prepare("SELECT * FROM message WHERE chat_id = ? AND is_file = true");
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
        message.is_file = query.value(5).toBool();
        message.setSenderName(query.value(6).toString());
        messages.append(message);
    }
    return messages;
}

QString DB::getName(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT name FROM user WHERE id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        return query.value(0).toString();
    }
    return "";
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

DB *DB::get_instance() {
    if (db == nullptr) {
        db = new DB;
    }
    return db;
}