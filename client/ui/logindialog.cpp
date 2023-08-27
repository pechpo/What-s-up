#include "logindialog.h"
#include "ui_logindialog.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QLocale>
#include <QTranslator>



LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_loginBtn_clicked()
{
    QMessageBox::information(NULL, tr("Note"), tr("Login success!"));//此处需要添加一个检查函数，来检验输入的用户名与密码是否正确，同时还缺少一个提示密码错误的信息。
    mw = new mainWindow();
    mw->show();
    accept();
}




void LoginDialog::on_closeButton_clicked()
{
    close();
}


void LoginDialog::on_closeButton_triggered(QAction *arg1)
{
    close();
}


void LoginDialog::on_minimizeButton_clicked()
{
    showMinimized();
}




void LoginDialog::on_ConnectionButton_clicked()
{
    lw = new LoginWindow;
    lw->show();
}