#include "logindialog.h"
#include "ui_logindialog.h"
#include "loginwindow.h"
#include "director/director.h"
#include <QMessageBox>
#include <QApplication>
#include <QLocale>
#include <QTranslator>


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

    connect(Director::getInstance(), &Director::r_login, this, &LoginDialog::slot_r_login);
}

LoginDialog::~LoginDialog()
{
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
        if (Director::getInstance()->sendJson(msg))
            waiting++;
    }
}

void LoginDialog::slot_r_login(const QJsonObject &msg) {
    waiting--;
    if (!msg.value("success").isBool()) {
        return ;
    }
    if (true == msg.value("success").toBool()) {
        Director::getInstance()->toMainWindow();
        accept();
    }
    else {
        if (msg.value("error").isString()) {
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
        lw = new LoginWindow(this);
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
        rd = new RegisterDialog();
        rd->show();
    }
    else {
        rd->close();
        rd->show();
    }
}

