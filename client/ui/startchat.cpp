#include "startchat.h"
#include "ui_startchat.h"

StartChat::StartChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartChat)
{
    ui->setupUi(this);
    bar = new ProfileBar(this);
    bar->move(0, 0);
    bar->show();
}

StartChat::~StartChat()
{
    delete bar;
    delete ui;
}

void StartChat::setName(const QString &name) {
    bar->setName(name);
}
