#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "director/director.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QVBoxLayout>

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
//    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    ui->setupUi(this);

    snf = nullptr;
    waiting = 0;
    this->setState(Friend);

    connect(Director::getInstance(), &Director::r_list_myFriends, this, &mainWindow::slot_r_list_myFriends);
    connect(Director::getInstance(), &Director::r_list_friendRequests, this, &mainWindow::slot_r_list_friendRequests);
    connect(Director::getInstance(), &Director::a_newFriendRequest, this, &mainWindow::slot_a_newFriendRequest);

    cw = new ChatWindow(this);
    cw->move(250, 50);
    cw->show();

    ui->closeButton->setVisible(false);
    ui->minimizeButton->setVisible(false);
    ui->GroupList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    /*friendRequests.resize(20);
    for (int i = 0; i < 20; i++) {
        friendRequests[i] = new AddNewFriend(ui->scrollAreaWidgetContents);
        friendRequests[i]->setId(i);
        friendRequests[i]->setName("Alice" + QString::number(i));
        friendRequests[i]->setAvatar("avatar");

    }
    friends.resize(2);
    friends[0] = new StartChat(ui->scrollAreaWidgetContents);
    friends[0]->setId(12345);
    friends[0]->setName("Dave");
    friends[0]->setAvatar("avatar");
    friends[1] = new StartChat(ui->scrollAreaWidgetContents);
    friends[1]->setId(54321);
    friends[1]->setName("Eva");
    friends[1]->setAvatar("avatar");
    waitingIsZero();*/
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
    //QVBoxLayout *layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    //layout->setSpacing(5);
    const quint32 gap = 5;
    quint32 height = gap;
    for (quint32 i = 0; i < friendRequests.size(); i++) {
        AddNewFriend *p = friendRequests[i];
        //layout->addWidget(p);
        p->move(gap, height);
        height += p->height() + gap;
        p->show();
    }
    for (quint32 i = 0; i < friends.size(); i++) {
        StartChat *p = friends[i];
        //layout->addWidget(p);
        p->move(gap, height);
        height += p->height() + gap;
        p->show();
    }
    ui->scrollAreaWidgetContents->adjustSize();
    //qDebug() << ui->scrollAreaWidgetContents->height();
}

void mainWindow::slot_r_list_myFriends(const QJsonObject &obj) {
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
    waiting--;
    if (0 == waiting) {
        waitingIsZero();
    }
}

void mainWindow::slot_r_list_friendRequests(const QJsonObject &obj) {
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
        //qDebug() << "add" + user.value("name").toString();
    }
    waiting--;
    if (0 == waiting) {
        waitingIsZero();
    }
}

void mainWindow::slot_a_newFriendRequest(const QJsonObject &obj) {
    setState(Friend);
}
