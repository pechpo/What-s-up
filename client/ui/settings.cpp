#include "settings.h"
#include "ui_settings.h"
#include "director/director.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    connect(Director::getInstance(), &Director::r_editInfo, this, &Settings::slot_r_editInfo);  //send signal to dialog window if r_login received
    connect(Director::getInstance(), &Director::r_myInfo, this, &Settings::slot_r_myInfo);  //send signal to dialog window if r_login received
    }

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    QJsonObject msg;
    msg.insert("type", "e_editInfo");
    msg.insert("old_pwd", Director::getInstance()->Hash(ui->currentPwd->text()));
    msg.insert("name", ui->newName->text());
    msg.insert("avatar", ui->newAvatar->text());
    msg.insert("email", ui->newEmail->text());
    msg.insert("password", Director::getInstance()->Hash(ui->newPwd->text()));
    Director::getInstance()->sendJson(msg);
}

void Settings::slot_r_editInfo(const QJsonObject &obj) {
    if (true == obj.value("success").toBool()) {
        QJsonObject msg;
        msg.insert("type", "q_myInfo");
        Director::getInstance()->sendJson(msg);
    }
}

void Settings::slot_r_myInfo(const QJsonObject &obj) {
    ui->idLabel->setText(QString::number(obj.value("id").toInt()));
    ui->newName->setText(obj.value("username").toString());
    ui->newAvatar->setText(obj.value("avatar").toString());
    ui->newEmail->setText(obj.value("email").toString());
    ui->currentPwd->setText("");
    ui->newPwd->setText("");
}

