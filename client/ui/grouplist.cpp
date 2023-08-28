#include "grouplist.h"
#include "ui_grouplist.h"

GroupList::GroupList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupList)
{
    ui->setupUi(this);
}

GroupList::~GroupList()
{
    delete ui;
}
