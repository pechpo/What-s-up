#include "settings.h"
#include "ui_settings.h"
#include "director/director.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    bar = new ProfileBar(ui->widget);

    QString confirmstyle = R"(
        QPushButton {
            border: none;
            background-color: rgba(4, 137, 152, 0.75);
            border-radius:10px;
        }
        QPushButton:hover {
            background-color: rgba(4, 137, 152, 1);
        }
    )";

    ui->pushButton->setStyleSheet(confirmstyle);

    connect(Director::getInstance(), &Director::r_editInfo, this, &Settings::slot_r_editInfo);  //send signal to dialog window if r_login received
    connect(Director::getInstance(), &Director::r_myInfo, this, &Settings::slot_r_myInfo);  //send signal to dialog window if r_login received
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    bool modifyPwd = (ui->newPwd->text().length() > 0);
    if (modifyPwd && ui->newPwd->text().length() < 4) {
        return ;
    }
    QJsonObject msg;
    msg.insert("type", "e_editInfo");
    msg.insert("old_pwd", Director::getInstance()->Hash(ui->currentPwd->text()));
    msg.insert("name", ui->newName->text());
    msg.insert("avatar", ui->newAvatar->text());
    msg.insert("email", ui->newEmail->text());
    if (modifyPwd) {
        msg.insert("password", Director::getInstance()->Hash(ui->newPwd->text()));
    }
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
    ui->idLabel->setText("ID: " + QString::number(obj.value("id").toInt()));
    QString name = obj.value("username").toString();
    QString avatar = obj.value("avatar").toString();
    ui->newName->setText(name);
    ui->newAvatar->setText(avatar);
    ui->newEmail->setText(obj.value("email").toString());
    ui->currentPwd->setText("");
    ui->newPwd->setText("");
    bar->setName(name);
    bar->setAvatar(avatar);
}

