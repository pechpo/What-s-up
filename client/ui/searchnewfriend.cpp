#include "searchnewfriend.h"
#include "ui_searchnewfriend.h"
#include <director/director.h>

#include <QJsonValue>

SearchNewFriend::SearchNewFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchNewFriend)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(50, 100);
    bar->show();

    userId = 0;
    waiting = 0;

    connect(Director::getInstance(), &Director::r_userInfo, this, &SearchNewFriend::slot_r_userInfo);
}

SearchNewFriend::~SearchNewFriend()
{
    delete ui;
}

void SearchNewFriend::on_SearchButton_clicked()
{
    if (0 == waiting) {
        qint64 id = ui->searchLineEdit->text().toInt();
        QJsonObject msg;
        msg.insert("type", "q_userInfo");
        msg.insert("id", QJsonValue(id));
        if (Director::getInstance()->sendJson(msg))
            waiting++;
    }
}

void SearchNewFriend::slot_r_userInfo(const QJsonObject &obj) {
    waiting--;
    if (!obj.value("id").isDouble()) {
        return ;
    }
    if (!obj.value("username").isString()) {
        return ;
    }
    userId = obj.value("id").toInt();
    bar->setName(obj.value("username").toString());
}

