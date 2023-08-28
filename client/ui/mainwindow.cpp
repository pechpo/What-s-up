#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "director/director.h"
#include <QJsonValue>
#include <QJsonArray>

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
//    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    ui->setupUi(this);

    snf = nullptr;
    this->setState(Friend);

    connect(Director::getInstance(), &Director::r_list_myFriends, this, &mainWindow::slot_r_list_myFriends);
    connect(Director::getInstance(), &Director::r_list_friendRequests, this, &mainWindow::slot_r_list_friendRequests);

    cw = new ChatWindow(this);
    cw->move(250, 50);
    cw->show();

    ui->closeButton->setVisible(false);
    ui->minimizeButton->setVisible(false);


    //for (quint16 i = 0; i < 50; i++)
    //    cw->appendText("Hello, world" + QString::number(i));
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
        Director::getInstance()->sendJson(msg1);
        QJsonObject msg2;
        msg2.insert("type", "q_list_friendRequests");
        Director::getInstance()->sendJson(msg2);
    }
    else if (curState == Chat) {

    }
    else {

    }
}

void mainWindow::slot_r_list_myFriends(const QJsonObject &obj) {
    if (false == obj.value("users").isArray()) {
        return ;
    }
    for (quint32 i = 0; i < friends.size(); i++) {
        delete friends[i];
    }
    friends.clear();
    QJsonArray users = obj.value("users").toArray();
    quint32 siz = users.size();
    friends.resize(siz);
    for (quint32 i = 0; i < siz; i++) {
        friends[i] = new StartChat(this);

    }
}

void mainWindow::slot_r_list_friendRequests(const QJsonObject &obj) {
    if (false == obj.value("users").isArray()) {
        return ;
    }
    for (quint32 i = 0; i < friendRequests.size(); i++) {
        delete friendRequests[i];
    }
    friendRequests.clear();
    QJsonArray users = obj.value("users").toArray();
    quint32 siz = users.size();
    friendRequests.resize(siz);
    for (quint32 i = 0; i < siz; i++) {
        friendRequests[i] = new AddNewFriend(this);

    }
}
