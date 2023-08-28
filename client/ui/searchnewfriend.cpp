#include "searchnewfriend.h"
#include "ui_searchnewfriend.h"

SearchNewFriend::SearchNewFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchNewFriend)
{
    ui->setupUi(this);
}

SearchNewFriend::~SearchNewFriend()
{
    delete ui;
}
