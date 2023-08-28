#include "startchat.h"
#include "ui_startchat.h"

StartChat::StartChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartChat)
{
    ui->setupUi(this);
}

StartChat::~StartChat()
{
    delete ui;
}
