#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "director/director.h"
#include <QJsonValue>
#include <QJsonArray>

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    ui->setupUi(this);

    snf = nullptr;
    waiting = 0;
    this->setState(Friend);

    connect(Director::getInstance(), &Director::r_list_myFriends, this, &mainWindow::slot_r_list_myFriends);
    connect(Director::getInstance(), &Director::r_list_friendRequests, this, &mainWindow::slot_r_list_friendRequests);

    cw = new ChatWindow(this);
    cw->move(250, 50);
    cw->show();
}

mainWindow::~mainWindow()
{
    for (quint32 i = 0; i < friends.size(); i++) {
        delete friends[i];
    }
    for (quint32 i = 0; i < friendRequests.size(); i++) {
        delete friendRequests[i];
    }
    delete snf;
    delete ui;
}

void mainWindow::on_closeButton_clicked()
{
    close();
}


void mainWindow::on_minimizeButton_clicked()
{
    showMinimized();
}


void mainWindow::on_addnewfriendButton_clicked()
{
    if (nullptr == snf) {
        snf = new SearchNewFriend();
        snf->show();
    }
    else {
        snf->close();
        snf->show();
    }
}

void mainWindow::setState(enum mainWindow::State tarState) {
    curState = tarState;
    if (curState == Friend) {
        QJsonObject msg1;
        msg1.insert("type", "q_list_myFriends");
        if (Director::getInstance()->sendJson(msg1)) {
            waiting++;
        }
        QJsonObject msg2;
        msg2.insert("type", "q_list_friendRequests");
        if (Director::getInstance()->sendJson(msg2)) {
            waiting++;
        }
    }
    else if (curState == Chat) {

    }
    else {

    }
}

void mainWindow::waitingIsZero() {
    quint32 height = 0;
    for (quint32 i = 0; i < friendRequests.size(); i++) {
        AddNewFriend *p = friendRequests[i];
        p->move(0, height);
        height += p->height();
        p->show();
    }
    for (quint32 i = 0; i < friends.size(); i++) {
        StartChat *p = friends[i];
        p->move(0, height);
        height += p->height();
        p->show();
    }
}

void mainWindow::slot_r_list_myFriends(const QJsonObject &obj) {
    waiting--;
    if (0 == waiting) {
        waitingIsZero();
    }
    if (false == obj.value("users").isArray()) {
        return ;
    }
    for (quint32 i = 0; i < friends.size(); i++) {
        friends[i]->close();
        delete friends[i];
    }
    friends.clear();
    QJsonArray users = obj.value("users").toArray();
    quint32 siz = users.size();
    friends.resize(siz);
    for (quint32 i = 0; i < siz; i++) {
        if (!users[i].isObject()) {
            continue ;
        }
        QJsonObject user = users[i].toObject();
        friends[i] = new StartChat(ui->scrollAreaWidgetContents);
        friends[i]->setId(user.value("id").toInt());
        friends[i]->setName(user.value("name").toString());
        friends[i]->setAvatar(user.value("avatar").toString());
    }
}

void mainWindow::slot_r_list_friendRequests(const QJsonObject &obj) {
    waiting--;
    if (0 == waiting) {
        waitingIsZero();
    }
    if (false == obj.value("users").isArray()) {
        return ;
    }
    for (quint32 i = 0; i < friendRequests.size(); i++) {
        friendRequests[i]->close();
        delete friendRequests[i];
    }
    friendRequests.clear();
    QJsonArray users = obj.value("users").toArray();
    quint32 siz = users.size();
    friendRequests.resize(siz);
    for (quint32 i = 0; i < siz; i++) {
        if (!users[i].isObject()) {
            continue ;
        }
        QJsonObject user = users[i].toObject();
        friendRequests[i] = new AddNewFriend(ui->scrollAreaWidgetContents);
        friendRequests[i]->setId(user.value("id").toInt());
        friendRequests[i]->setName(user.value("name").toString());
        friendRequests[i]->setAvatar(user.value("avatar").toString());
    }
}
