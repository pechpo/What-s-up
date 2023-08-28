#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "director/director.h"

#include <QJsonArray>

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->MsgEdit->setReadOnly(true);
    chatId = 0;

    connect(Director::getInstance(), &Director::r_chatHistory, this, &ChatWindow::slot_r_chatHistory);
    connect(Director::getInstance(), &Director::a_newMessage, this, &ChatWindow::slot_a_newMessage);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

bool ChatWindow::isThisChat(const QJsonObject &obj) {
    if (!obj.value("chatId").isDouble()) {
        return false;
    }
    int recvId = obj.value("chatId").toInt();
    return (recvId == chatId);
}

void ChatWindow::switchChat(qint64 id) {
    if (id == chatId) {
        return ;
    }
    chatId = id;
    ui->MsgEdit->setText("");
    QJsonObject msg;
    msg.insert("type", "q_chatHistory");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("count", 64);
    Director::getInstance()->sendJson(msg);
}

void ChatWindow::slot_r_chatHistory(const QJsonObject &obj) {
    if (!isThisChat(obj)) {
        return ;
    }
    if (!obj.value("chatHistory").isArray()) {
        return ;
    }
    // todo: insert chatHistory message to proper place
    // current: reset
    QJsonArray recvHistory = obj.value("chatHistory").toArray();
    quint32 recvSize = recvHistory.size();
    history.clear();
    history.resize(recvSize);
    for (int i = 0; i < recvSize; i++) {
        history[i] = jsonToMessage(recvHistory.at(i).toObject());
    }
    updateText();
}

void ChatWindow::slot_a_newMessage(const QJsonObject &obj) {
    if (!isThisChat(obj)) {
        return ;
    }
    Message cur = jsonToMessage(obj);
    history.append(cur);
    appendText(messageToString(cur));
}

ChatWindow::Message ChatWindow::jsonToMessage(const QJsonObject &obj) {
    Message cur;
    auto setIncompleteMessage = [] (Message &cur) -> void {
        cur.isSystem = true;
        cur.content = "Incomplete Message.";
    };
    if (!obj.value("senderId").isDouble()) {
        setIncompleteMessage(cur);
        return cur;
    }
    if (!obj.value("senderName").isString()) {
        setIncompleteMessage(cur);
        return cur;
    }
    if (!obj.value("content").isString()) {
        setIncompleteMessage(cur);
        return cur;
    }
    //
    if (obj.value("isSystem").isString()) {
        cur.isSystem = true;
    }
    else {
        cur.isSystem = false;
        cur.senderId = obj.value("senderId").toInt();
        cur.senderName = obj.value("senderName").toString();
    }
    cur.content = obj.value("content").toString();
    return cur;
}

QString ChatWindow::messageToString(const Message &cur) {
    QString one;
    one.append(cur.senderName);
    one.append(" (" + QString::number(cur.senderId) + ")\n");
    one.append(cur.content + "\n");
    return one;
}

void ChatWindow::updateText() {
    // QVector<Message> history -> lineEdit->text()
    QString all;
    for (quint32 i = 0; i < history.size(); i++) {
        all.append(messageToString(history[i]));
    }
    ui->MsgEdit->setPlainText(all);
}

void ChatWindow::appendText(const QString &text) {
    ui->MsgEdit->insertPlainText(text + "\n");
}
