#include "addnewfriend.h"
#include "ui_addnewfriend.h"
#include "director/director.h"
#include <QJsonObject>
#include <QJsonValue>

AddNewFriend::AddNewFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewFriend)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(0, 0);
    bar->show();
    bar->stackUnder(this);
    ui->acceptButton->raise();
    ui->declineButton->raise();
    ui->acceptButton->setToolTip("通过");
    ui->declineButton->setToolTip("拒绝");

    connect(Director::getInstance(), &Director::r_acceptFriend, this, &AddNewFriend::slot_r_acceptFriend);

}

AddNewFriend::~AddNewFriend()
{
    delete bar;
    delete ui;
}

void AddNewFriend::setId(quint32 newId) {
    id = newId;
}

void AddNewFriend::setName(const QString &name) {
    bar->setName(name);
}

void AddNewFriend::setAvatar(const QString &avatar) {
    bar->setAvatar(avatar);
}

void AddNewFriend::on_acceptButton_clicked()
{
    QJsonObject msg;
    msg.insert("type", "e_acceptFriend");
    msg.insert("id", QJsonValue(id));
    msg.insert("accept", true);
    if (Director::getInstance()->sendJson(msg)) {

    }
}

void AddNewFriend::on_declineButton_clicked()
{
    QJsonObject msg;
    msg.insert("type", "e_acceptFriend");
    msg.insert("id", QJsonValue(id));
    msg.insert("accept", false);
    if (Director::getInstance()->sendJson(msg)) {

    }
}

void AddNewFriend::slot_r_acceptFriend(const QJsonObject &obj) {
    if (true == obj.value("success").toBool()) {
        Director::getInstance()->refreshMainWindow(Director::Friend);
    }
}
