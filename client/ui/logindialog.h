#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QMouseEvent>
#include "loginwindow.h"
#include "registerdialog.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();


signals:

public slots:
    void slot_r_login(const QJsonObject&);

private slots:

    void on_loginBtn_clicked();

    void on_closeButton_clicked();

    void on_closeButton_triggered(QAction *arg1);

    void on_ConnectionButton_clicked();

    void on_regBtn_clicked();

private:
    Ui::LoginDialog *ui;
    LoginWindow *lw;
    RegisterDialog *rd;
    quint32 waiting;
};

#endif // LOGINDIALOG_H
