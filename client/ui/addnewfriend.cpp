#include "addnewfriend.h"
#include "ui_addnewfriend.h"

AddNewFriend::AddNewFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewFriend)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(0, 0);
    bar->show();
}

AddNewFriend::~AddNewFriend()
{
    delete bar;
    delete ui;
}

void AddNewFriend::setName(const QString &name) {
    bar->setName(name);
}
