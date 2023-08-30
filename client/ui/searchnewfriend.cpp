#include "searchnewfriend.h"
#include "ui_searchnewfriend.h"

#include <QJsonValue>

SearchNewFriend::SearchNewFriend(QWidget *parent) :
    QWidget(parent),
    curState(Director::Friend),
    ui(new Ui::SearchNewFriend)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(50, 100);
    bar->show();

    userId = 0;
    waiting = 0;

    ui->switchButton->setToolTip(tr("搜索好友/群聊"));

    connect(Director::getInstance(), &Director::r_userInfo, this, &SearchNewFriend::slot_r_userInfo);
    connect(Director::getInstance(), &Director::r_chatInfo, this, &SearchNewFriend::slot_r_chatInfo);
    connect(Director::getInstance(), &Director::r_addFriend, this, &SearchNewFriend::slot_r_addFriend);
    connect(Director::getInstance(), &Director::r_joinChat, this, &SearchNewFriend::slot_r_joinChat);
}

SearchNewFriend::~SearchNewFriend()
{
    delete bar;
    delete ui;
}

void SearchNewFriend::on_SearchButton_clicked()
{
    if (0 == waiting) {
        qint64 id = userId = ui->searchLineEdit->text().toInt();
        QJsonObject msg;
        if (Director::Friend == curState) {
            msg.insert("type", "q_userInfo");
            msg.insert("id", QJsonValue(id));
        }
        else if (Director::Chat == curState) {
            msg.insert("type", "q_chatInfo");
            msg.insert("chatId", QJsonValue(id));
        }
        if (Director::getInstance()->sendJson(msg))
            waiting++;
    }
}

void SearchNewFriend::slot_r_userInfo(const QJsonObject &obj) {
    waiting--;
    if (0 == obj.value("username").toString().length()) {
        bar->setName(tr("查无此人。"));
        return ;
    }
    bar->setName(obj.value("username").toString());
    bar->setAvatar(obj.value("avatar").toString());
}

void SearchNewFriend::slot_r_chatInfo(const QJsonObject &obj) {
    waiting--;
    if (0 == obj.value("name").toString().length()) {
        bar->setName(tr("查无此群。"));
        return ;
    }
    bar->setName(obj.value("name").toString());
    bar->setAvatar(obj.value("avatar").toString());
}

void SearchNewFriend::on_confirmButton_clicked()
{
    if (0 == waiting) {
        qint64 id = ui->searchLineEdit->text().toInt();
        QJsonObject msg;
        if (Director::Friend == curState) {
            msg.insert("type", "e_addFriend");
            msg.insert("id", QJsonValue(id));
        }
        else if (Director::Chat == curState) {
            msg.insert("type", "e_joinChat");
            msg.insert("chatId", QJsonValue(id));
        }
        if (Director::getInstance()->sendJson(msg))
            waiting++;
    }
}

void SearchNewFriend::slot_r_addFriend(const QJsonObject &obj) {
    waiting--;
    close();
}

void SearchNewFriend::slot_r_joinChat(const QJsonObject &obj) {
    waiting--;
    Director::getInstance()->refreshMainWindow(Director::Chat);
    close();
}

void SearchNewFriend::clear() {
    userId = 0;
    ui->searchLineEdit->setText("");
    bar->setName(tr("Searching..."));
}

void SearchNewFriend::on_switchButton_clicked()
{
    clear();
    if (Director::Friend == curState) {
        curState = Director::Chat;
        ui->SearchButton->setText(tr("搜索聊天"));
        ui->confirmButton->setText(tr("加入聊天"));
    }
    else if (Director::Chat == curState) {
        curState = Director::Friend;
        ui->SearchButton->setText(tr("搜索好友"));
        ui->confirmButton->setText(tr("添加好友"));
    }
}

