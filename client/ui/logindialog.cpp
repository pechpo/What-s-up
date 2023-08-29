#include "logindialog.h"
#include "ui_logindialog.h"
#include "loginwindow.h"
#include "director/director.h"
#include <QMessageBox>
#include <QApplication>
#include <QLocale>
#include <QTranslator>


//login dialog initializing
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    this->installEventFilter(this);
    ui->setupUi(this);

    ui->closeButton->setVisible(false);
    ui->minimizeButton->setVisible(false);

    lw = nullptr;
    rd = nullptr;
    waiting = 0;

    connect(Director::getInstance(), &Director::r_login, this, &LoginDialog::slot_r_login);  //send signal to dialog window if r_login received
}

LoginDialog::~LoginDialog()
{
    lw->close();
    rd->close();
    delete lw;
    delete rd;
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    if (0 == waiting) {
        qint64 id = ui->usrLineEdit->text().toInt();
        QString pwd = Director::getInstance()->Hash(ui->pwdLineEdit->text());
        QJsonObject msg;
        msg.insert("type", "q_login");
        msg.insert("id", QJsonValue(id));
        msg.insert("password", QJsonValue(pwd));
        if (Director::getInstance()->sendJson(msg))  //sending login information
            waiting++;
    }
}

void LoginDialog::slot_r_login(const QJsonObject &msg) {
    waiting--;  //login feedback recieved
    if (!msg.value("success").isBool()) {
        return ;
    }
    if (true == msg.value("success").toBool()) {
        Director::getInstance()->toMainWindow();  //if success, go to mainwindow
        accept();
    }
    else {
        if (msg.value("error").isString()) {  //if not, print error
            qDebug() << msg.value("error").toString();
        }
    }
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
    if (nullptr == lw) {
        lw = new LoginWindow();  //create login subwindow
        lw->show();
    }
    else {
        lw->close();
        lw->show();
    }
}

void LoginDialog::on_regBtn_clicked()
{
    if (nullptr == rd) {
        rd = new RegisterDialog();  //create register subwindow
        rd->show();
    }
    else {
        rd->close();
        rd->show();
    }
}

