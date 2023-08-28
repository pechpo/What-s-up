#include "addnewfriend.h"
#include "ui_addnewfriend.h"

AddNewFriend::AddNewFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewFriend)
{
    ui->setupUi(this);
}

AddNewFriend::~AddNewFriend()
{
    delete ui;
}
