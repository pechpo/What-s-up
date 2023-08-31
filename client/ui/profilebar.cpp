#include "profilebar.h"
#include "ui_profilebar.h"
#include "director/director.h"

ProfileBar::ProfileBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileBar)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的

}

ProfileBar::~ProfileBar()
{
    delete ui;
}

void ProfileBar::setName(const QString &name) {
    ui->username->setText(name);
}

void ProfileBar::setAvatar(const QString &newAvatar) {
    avatar = newAvatar;
    QString imagePath = Director::getInstance()->genAvatarPath(avatar);
    QString style = QString("border-image: url(%1);").arg(imagePath);
    ui->avatar->setStyleSheet(style);
}

QString ProfileBar::getName() {
    return ui->username->text();
}
