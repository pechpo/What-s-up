#include "db.h"
#include <QSqlQuery>
#include "recommendation.h"

//user id, name, password, avatar, email
//message id, chat_id, sender_id, content, time, sender_name, is_file, file_name, format
//chat id, name, avatar
//friend_request user_id, friend_id
//friend user_id, friend_id, chat_id
//user_tags user_id, tag0, tag1, ..., tag35

DB *DB::db = nullptr;

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

DB *DB::get_instance() {
    if (db == nullptr) {
        db = new DB;
    }
    return db;
}

int DB::new_chat_id() {
    QSqlQuery query(database);
    query.prepare("SELECT MAX(id) FROM chat");
    query.exec();
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}

int DB::new_message_id() {
    QSqlQuery query(database);
    query.prepare("SELECT MAX(id) FROM message");
    query.exec();
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}

bool DB::e_register(const User &user) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO user (id, name, password, avatar, email) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(user.getID());
    query.addBindValue(user.getName());
    query.addBindValue(user.getPwd());
    query.addBindValue(user.getAvatarName());
    query.addBindValue(user.getEmail());
    init_tags(user.getID());
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

bool DB::e_edit_name(const User &user) {
    if (user.getName() == "")return true;
    QSqlQuery query(database);
    query.prepare("UPDATE user SET name = ? WHERE id = ?");
    query.addBindValue(user.getName());
    query.addBindValue(user.getID());
    return query.exec();
}

bool DB::e_edit_password(const User &user) {
    if (user.getPwd() == "")return true;
    QSqlQuery query(database);
    query.prepare("UPDATE user SET password = ? WHERE id = ?");
    query.addBindValue(user.getPwd());
    query.addBindValue(user.getID());
    return query.exec();
}

bool DB::e_edit_avatar(const User &user) {
    if (user.getAvatarName() == "")return true;
    QSqlQuery query(database);
    query.prepare("UPDATE user SET avatar = ? WHERE id = ?");
    query.addBindValue(user.getAvatarName());
    query.addBindValue(user.getID());
    return query.exec();
}

bool DB::e_edit_email(const User &user) {
    if (user.getEmail() == "")return true;
    QSqlQuery query(database);
    query.prepare("UPDATE user SET email = ? WHERE id = ?");
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
    query.addBindValue(ID);
    query.addBindValue(name);
    query.addBindValue(avatarName);
    return query.exec();
}

bool DB::e_joinChat(const quint32 &ID, const quint32 &chat_ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM friend WHERE chat_id = ?");
    query.addBindValue(chat_ID);
    query.exec();
    if (query.next())return false;
    query.clear();

    query.prepare("INSERT INTO user_chat (user_id, chat_id) VALUES (?, ?)");
    query.addBindValue(ID);
    query.addBindValue(chat_ID);
    return query.exec();
}

QList<chat> DB::q_list_myChats(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT chat_id FROM user_chat WHERE user_id = ?");
    query.addBindValue(ID);
    query.exec();
    QList<chat> chats;
    while (query.next()) {
        chat chat;
        QSqlQuery Query(database);
        Query.prepare("SELECT * FROM chat WHERE id = ?");
        Query.addBindValue(query.value(0).toUInt());
        Query.exec();
        if (!Query.next())continue;
        chat.setID(Query.value(0).toUInt());
        chat.setName(Query.value(1).toString());
        chat.setAvatarName(Query.value(2).toString());
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
        if (!Query.next())continue;
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
        qDebug() << query.value(0).toUInt();
        Query.addBindValue(query.value(0).toUInt());
        Query.exec();
        if (!Query.next())continue;
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
        if (!Query.next())continue;
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
        int chat = new_chat_id();

        e_joinChat(id, chat);
        e_joinChat(ID, chat);

        query.prepare("INSERT INTO friend (user_id, friend_id, chat_id) VALUES (?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(ID);
        query.addBindValue(chat);
        query.exec();

        query.clear();
        query.prepare("INSERT INTO friend (user_id, friend_id, chat_id) VALUES (?, ?, ?)");
        query.addBindValue(ID);
        query.addBindValue(id);
        query.addBindValue(chat);
        query.exec();

        e_createChat(chat, "default", "");
    }
    query.clear();
    query.prepare("DELETE FROM friend_request WHERE user_id = ? AND friend_id = ?");
    query.addBindValue(ID);
    query.addBindValue(id);
    return query.exec();
}

bool DB::e_send(const Message &message) {
    QSqlQuery query(database);
    query.prepare(
            "INSERT INTO message (id, chat_id, sender_id, content, time, sender_name, is_file, file_name, format) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(message.getID());
    query.addBindValue(message.getReceiverID());
    query.addBindValue(message.getSenderID());
    query.addBindValue(message.getContent());
    query.addBindValue(message.getTime());
    query.addBindValue(message.getSenderName());
    query.addBindValue(message.getIsFile());
    query.addBindValue(message.getFileName());
    query.addBindValue(message.getFormat());
    return query.exec();
}

QList<Message> DB::q_chatHistory(const quint32 &chat_ID, const quint32 &time, const quint32 &count) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM message WHERE chat_id = ?");
    query.addBindValue(chat_ID);
//    query.addBindValue(time);
//    query.addBindValue(count);
    query.exec();
    QList<Message> messages;
    while (query.next()) {
        Message message;
        message.setID(query.value(0).toUInt());
        message.setReceiverID(query.value(1).toUInt());
        message.setSenderID(query.value(2).toUInt());
        message.setContent(query.value(3).toString());
        message.setTime(query.value(4).toString());
        message.setSenderName(query.value(5).toString());
        message.setIsFile(query.value(6).toBool());
        message.setFileName(query.value(7).toString());
        message.setFormat(query.value(8).toString());
        messages.append(message);
    }
    return messages;
}

QString DB::getChatName(const int &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT name FROM chat WHERE id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        return query.value(0).toString();
    }
    return "";
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
        message.setSenderName(query.value(5).toString());
        message.setIsFile(query.value(6).toBool());
        message.setFileName(query.value(7).toString());
        message.setFormat(query.value(8).toString());
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

bool DB::check(const int &id, const int &chat) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user_chat WHERE user_id = ? AND chat_id = ?");
    query.addBindValue(id);
    query.addBindValue(chat);
    query.exec();
    if (query.next())return true;
    return false;
}

bool DB::uploadFileToFTP(const QString &filename) {
/*    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string url = "ftp://192.168.66.128:21";
        url += filename.toStdString();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERNAME, "usr");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "123");

        // 更多的设置和错误处理...

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return false;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return true;*/
    return true;
}

std::pair<QString, QString> DB::q_downloadFile(const int &ID, const QString &fileName) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM message WHERE chat_id = ? AND file_name = ?");
    query.addBindValue(ID);
    query.addBindValue(fileName);
    query.exec();
    if (query.next())return {query.value(3).toString(), query.value(8).toString()};
    return {"", ""};
}

std::tuple<QString, QString, QList<User>> DB::q_chatInfo(const quint32 &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM chat WHERE id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        QString name = query.value(1).toString();
        QString avatar = query.value(2).toString();
        QList<User> users = q_list_usersInChat(ID);
        return std::make_tuple(name, avatar, users);
    }
    return std::make_tuple("", "", QList<User>({}));
}

bool DB::e_editChatInfo(const quint32 &ID, const QString &name, const QString &avatar) {
    QSqlQuery query(database);
    query.prepare("UPDATE chat SET name = ?, avatar = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(avatar);
    query.addBindValue(ID);
    return query.exec();
}

int DB::q_talk(const int &id, const int &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM friend WHERE user_id = ? AND friend_id = ?");
    query.addBindValue(id);
    query.addBindValue(ID);
    query.exec();
    if (query.next())return query.value(2).toInt();
    return 0;
}

bool DB::add_tag(const int &ID, const std::vector<int> &tags) {
    QSqlQuery query(database);
    query.prepare(
            "UPDATE user_tags SET tag0 = ?, tag1 = ?, tag2 = ?, tag3 = ?, tag4 = ?, tag5 = ?, tag6 = ?, tag7 = ?, tag8 = ?, tag9 = ?, tag10 = ?, tag11 = ?, tag12 = ?, tag13 = ?, tag14 = ?, tag15 = ?, tag16 = ?, tag17 = ?, tag18 = ?, tag19 = ?, tag20 = ?, tag21 = ?, tag22 = ?, tag23 = ?, tag24 = ?, tag25 = ?, tag26 = ?, tag27 = ?, tag28 = ?, tag29 = ?, tag30 = ?, tag31 = ?, tag32 = ?, tag33 = ?, tag34 = ?, tag35 = ? WHERE user_id = ?");

    for (int i = 0; i < 36; i++) {
        query.addBindValue(tags[i]);
    }
    query.addBindValue(ID);
    return query.exec();
}

std::vector<int> DB::q_list_tags(const int &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user_tags WHERE user_id = ?");
    query.addBindValue(ID);
    query.exec();
    if (query.next()) {
        std::vector<int> tags;
        for (int i = 0; i < 36; i++) {
            tags.push_back(query.value(i + 1).toInt());
        }
        return tags;
    }
    return {};
}

std::unordered_map<quint32, std::vector<int>> DB::get_all_tags() {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user_tags");
    query.exec();
    std::unordered_map<quint32, std::vector<int>> users;
    while (query.next()) {
        std::vector<int> tags;
        for (int i = 0; i < 36; i++) {
            tags.push_back(query.value(i + 1).toInt());
        }
        users[query.value(0).toInt()] = tags;
    }
    return users;
}

std::vector<quint32> DB::getFriends(const int &ID) {
    QSqlQuery query(database);
    query.prepare("SELECT friend_id FROM friend WHERE user_id = ?");
    query.addBindValue(ID);
    query.exec();
    std::vector<quint32> friends;
    while (query.next()) {
        friends.push_back(query.value(0).toInt());
    }
    return friends;
}

bool DB::e_exitChat(const int &ID, const int &chatId) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM friend WHERE chat_id = ?");
    query.addBindValue(chatId);
    query.exec();
    if (query.next()) {
        auto x = query.value(0).toInt();
        auto y = query.value(1).toInt();

        query.clear();
        query.prepare("DELETE FROM friend WHERE user_id = ? AND chat_id = ?");
        query.addBindValue(x);
        query.addBindValue(chatId);
        query.exec();

        query.clear();
        query.prepare("DELETE FROM friend WHERE user_id = ? AND chat_id = ?");
        query.addBindValue(y);
        query.addBindValue(chatId);
        query.exec();

        query.clear();
        query.prepare("DELETE FROM user_chat WHERE user_id = ? AND chat_id = ?");
        query.addBindValue(x);
        query.addBindValue(chatId);
        query.exec();

        query.clear();
        query.prepare("DELETE FROM user_chat WHERE user_id = ? AND chat_id = ?");
        query.addBindValue(x);
        query.addBindValue(chatId);
        query.exec();

        return true;
    }
    query.clear();
    query.prepare("DELETE FROM user_chat WHERE user_id = ? AND chat_id = ?");
    query.addBindValue(ID);
    query.addBindValue(chatId);
    return query.exec();
}

bool DB::init_tags(const int &ID) {
    QSqlQuery query(database);
    query.prepare(
            "INSERT INTO user_tags (user_id, tag0, tag1, tag2, tag3, tag4, tag5, tag6, tag7, tag8, tag9, tag10, tag11, tag12, tag13, tag14, tag15, tag16, tag17, tag18, tag19, tag20, tag21, tag22, tag23, tag24, tag25, tag26, tag27, tag28, tag29, tag30, tag31, tag32, tag33, tag34, tag35) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

    query.addBindValue(ID);
    for (int i = 0; i < 36; i++) {
        query.addBindValue(0);
    }
    return query.exec();
}

QList<User> DB::q_list_recommend(const int &ID) {
    Recommendation *rd = Recommendation::get_instance();
    auto U = rd->recommendFriends(ID);
    QList<User> users;
    qDebug() << U;
    for (const auto &id: U) {
        users.append(q_userInfo(id));
    }
    return users;
}
