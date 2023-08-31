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
    ui->chatButton->setStyleSheet("QPushButton{border:none;image: url(:/images/image/message.png);}");
    bar = new ProfileBar(this);
    bar->move(0, 0);
    bar->show();
    bar->stackUnder(this);
    ui->chatButton->raise();
    ui->chatButton->setToolTip(tr("进入聊天/群聊"));
    ui->newMsgLabel->setVisible(false);

    hasNew = false;
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
    // 枣树
    if (isPerson) {
        bar->setName(name);
    }
    else {
        bar->setName(name);
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
        msg.insert("type", "q_talk");
        msg.insert("id", QJsonValue(id));
        Director::getInstance()->sendJson(msg);
    }
    else {
        setNewTag(false);
        Director::getInstance()->enterChat(id);
    }
}

qint64 StartChat::getId() {
    return id;
}

QString StartChat::getName() {
    return bar->getName();
}

void StartChat::setNewTag(bool tag) {
    hasNew = tag;
    ui->newMsgLabel->setVisible(tag);
}
