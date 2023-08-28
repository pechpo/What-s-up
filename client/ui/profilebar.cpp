#include "profilebar.h"
#include "ui_profilebar.h"

ProfileBar::ProfileBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileBar)
{
    ui->setupUi(this);
}

ProfileBar::~ProfileBar()
{
    delete ui;
}

void ProfileBar::setName(const QString &name) {
    ui->username->setText(name);
}
