#include "startchat.h"
#include "ui_startchat.h"
#include "director/director.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

StartChat::StartChat(QWidget *parent, bool isRealPerson) :
    QWidget(parent),
    ui(new Ui::StartChat),
    isPerson(isRealPerson)
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
    if (isPerson) {
        bar->setName(name);
    }
    else {
        bar->setName("Chat " + name);
    }
}

void StartChat::setAvatar(const QString &avatar) {
    bar->setAvatar(avatar);
}

void StartChat::on_chatButton_clicked()
{
    if (isPerson) {
        qDebug() << "si liao";
        QJsonObject msg;
        QJsonArray arr;
        arr.push_back(QJsonValue(id));
        msg.insert("type", "e_createChat");
        msg.insert("users", arr);
        Director::getInstance()->sendJson(msg);
    }
    else {
        Director::getInstance()->enterChat(id);
    }
}

qint64 StartChat::getId() {
    return id;
}

QString StartChat::getName() {
    return bar->getName();
}

