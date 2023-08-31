#include "friendrequest.h"
#include "ui_friendrequest.h"
#include "director/director.h"
#include <QJsonValue>

FriendRequest::FriendRequest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendRequest)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(0, 0);
    bar->show();
    bar->stackUnder(this);
    ui->requestButton->raise();

    alreadySend = false;

    connect(Director::getInstance(), &Director::r_addFriend, this, &FriendRequest::slot_r_addFriend);
}

FriendRequest::~FriendRequest()
{
    delete ui;
}

void FriendRequest::setId(quint32 newId) {
    id = newId;
}

void FriendRequest::setName(const QString &name) {
    bar->setName(name);
}

void FriendRequest::setAvatar(const QString &avatar) {
    bar->setAvatar(avatar);
}

void FriendRequest::on_requestButton_clicked()
{
    if (false == alreadySend) {
        QJsonObject msg;
        msg.insert("type", "e_addFriend");
        msg.insert("id", QJsonValue(id));
        if (Director::getInstance()->sendJson(msg)) {
            alreadySend = true;
        }
    }
}

void FriendRequest::slot_r_addFriend(const QJsonObject &obj) {
    if (alreadySend && true == obj.value("success").toBool()) {
        ui->requestButton->setVisible(false);
    }
}
