#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "director/director.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    waiting = 0;

    connect(Director::getInstance(), &Director::r_register, this, &RegisterDialog::slot_r_register);

    ui->closeButton->setVisible(false);
    ui->minimizeButton->setVisible(false);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_confirmBtn_clicked() {
    if (0 == waiting) {
        if (ui->confirmPwdLineEdit->text() != ui->pwdLineEdit->text()) {
            // todo
            return ;
        }
        QJsonObject msg;
        qint64 id = ui->usrLineEdit->text().toInt();
        QString pwd = Director::getInstance()->Hash(ui->pwdLineEdit->text());
        msg.insert("type", "e_register");
        msg.insert("id", QJsonValue(id));
        msg.insert("password", QJsonValue(pwd));
        msg.insert("username", QJsonValue("Bob" + QString::number(id)));
        msg.insert("email", QJsonValue(QString::number(id) + "@bit.edu.cn"));
        msg.insert("avatar", QJsonValue("hereIsAvatar" + QString::number(id)));
        if (Director::getInstance()->sendJson(msg))
            waiting++;
    }
}

void RegisterDialog::slot_r_register(const QJsonObject &msg) {
    waiting--;
    if (!msg.value("success").isBool()) {
        return ;
    }
    if (true == msg.value("success").toBool()) {
        QJsonObject msg;
        msg.insert("type", "e_joinChat");
        msg.insert("chatId", 1);
        Director::getInstance()->sendJson(msg);
        accept();
        close();
    }
    else {
        if (msg.value("error").isString()) {
            qDebug() << msg.value("error").toString();
        }
    }
}

void RegisterDialog::on_closeButton_clicked()
{
    close();
}


void RegisterDialog::on_minimizeButton_clicked()
{
    showMinimized();
}


