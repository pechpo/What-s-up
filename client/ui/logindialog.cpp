#include "logindialog.h"
#include "ui_logindialog.h"
//#include "ui_loginwindow.h"
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
    QString style = R"(
    QDialog {
        border-radius: 60px;
        background-color: white;
    }
    )";
    this->setStyleSheet(style);
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_loginBtn_clicked()
{
    QMessageBox::information(NULL, tr("Note"), tr("Login success!"));
    accept();
}






