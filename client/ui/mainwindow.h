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
#include "tageditor.h"
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
    void setState(enum Director::State, bool noRefresh = false);
    ChatWindow* getChatWindow();
    void raiseChat(qint64 chatId);

public slots:
    void slot_r_list_myFriends(const QJsonObject&);
    void slot_r_list_friendRequests(const QJsonObject&);
    void slot_a_newFriendRequest(const QJsonObject&);
    void slot_r_list_myChats(const QJsonObject&);
    void slot_a_newChat(const QJsonObject&);
    void slot_a_newMessage(const QJsonObject&);

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_addnewfriendButton_clicked();

    void on_grouplistButton_clicked();

    void on_settingButton_clicked();

    void on_NewGroupButton_clicked();

    void on_tagsButton_clicked();

private:
    Ui::mainWindow *ui;
    ChatWindow *cw;
    SearchNewFriend *snf;
    CreateChat *newChatDialog;
    Settings *settings;
    TagEditor *tags;
    QVector<AddNewFriend*> friendRequests;
    QVector<StartChat*> friends;
    QVector<StartChat*> chats;
    quint32 waiting;
    Director::State curState;
    void waitingIsZero();
};

#endif // MAINWINDOW_H
