#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

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

private slots:

    void on_loginBtn_clicked();


    //void on_toolButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H