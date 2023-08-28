#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "director/director.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    chatId = 0;

    connect(Director::getInstance(), &Director::r_chatHistory, this, &ChatWindow::on_r_chatHistory);
    connect(Director::getInstance(), &Director::a_newMessage, this, &ChatWindow::on_a_newMessage);
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
    chatId = id;
    QJsonObject msg;
    msg.insert("type", "q_chatHistory");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("count", 64);
    Director::getInstance()->sendJson(msg);
}

void ChatWindow::on_r_chatHistory(const QJsonObject &obj) {
    if (!isThisChat(obj)) {
        return ;
    }
    // insert to proper place in history
}

void ChatWindow::on_a_newMessage(const QJsonObject &obj) {
    if (!isThisChat(obj)) {
        return ;
    }

}

void updateText() {
    // QVector<Message> history -> lineEdit->text()
}

void ChatWindow::appendText(const QString &text) {
    ui->MsgEdit->insertPlainText(text + "\n");
}
