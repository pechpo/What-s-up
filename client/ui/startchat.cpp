#include "startchat.h"
#include "ui_startchat.h"
#include "director/director.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

StartChat::StartChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartChat)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(0, 0);
    bar->show();
    bar->stackUnder(this);
    ui->chatButton->raise();
}

StartChat::~StartChat()
{
    delete bar;
    delete ui;
}

void StartChat::setId(quint32 newId) {
    id = newId;
}

void StartChat::setName(const QString &name) {
    bar->setName(name);
}

void StartChat::setAvatar(const QString &avatar) {
    bar->setAvatar(avatar);
}

void StartChat::on_chatButton_clicked()
{
    QJsonObject msg;
    QJsonArray arr;
    msg.insert("type", "e_createChat");
    arr.push_back(QJsonValue(id));
    msg.insert("users", arr);
    if (Director::getInstance()->sendJson(msg)) {
        Director::getInstance()->refreshMainWindow();
    }
}

