#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QJsonObject>
#include "chatwindow.h"
#include "searchnewfriend.h"
#include "addnewfriend.h"
#include "startchat.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
    enum State {
        Friend, Chat
    } curState;
    void setState(State);

public slots:
    void slot_r_list_myFriends(const QJsonObject&);
    void slot_r_list_friendRequests(const QJsonObject&);

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_addnewfriendButton_clicked();

private:
    Ui::mainWindow *ui;
    ChatWindow *cw;
    SearchNewFriend *snf;
    QVector<AddNewFriend*> friendRequests;
    QVector<StartChat*> friends;
    quint32 waiting;
    void waitingIsZero();
};

#endif // MAINWINDOW_H
