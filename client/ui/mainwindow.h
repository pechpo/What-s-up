#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "chatwindow.h"
#include "searchnewfriend.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_addnewfriendButton_clicked();

private:
    Ui::mainWindow *ui;
    ChatWindow *cw;
    SearchNewFriend *snf;
};

#endif // MAINWINDOW_H
