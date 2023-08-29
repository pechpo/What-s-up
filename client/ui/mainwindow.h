#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QJsonObject>
#include "chatwindow.h"
#include "searchnewfriend.h"
#include "addnewfriend.h"
#include "startchat.h"
#include "createchat.h"
#include "settings.h"
#include "director/director.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
    void setState(enum Director::State);
    ChatWindow* getChatWindow();

public slots:
    void slot_r_list_myFriends(const QJsonObject&);
    void slot_r_list_friendRequests(const QJsonObject&);
    void slot_a_newFriendRequest(const QJsonObject&);
    void slot_r_list_myChats(const QJsonObject&);
    void slot_a_newChat(const QJsonObject&);

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_addnewfriendButton_clicked();

    void on_toolButton_clicked();

    void on_grouplistButton_clicked();

    void on_settingButton_clicked();

private:
    Ui::mainWindow *ui;
    ChatWindow *cw;
    SearchNewFriend *snf;
    CreateChat *newChatDialog;
    Settings *settings;
    QVector<AddNewFriend*> friendRequests;
    QVector<StartChat*> friends;
    QVector<StartChat*> chats;
    quint32 waiting;
    Director::State curState;
    void waitingIsZero();
};

#endif // MAINWINDOW_H
