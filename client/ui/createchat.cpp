#include "createchat.h"
#include "ui_createchat.h"

CreateChat::CreateChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);
}

CreateChat::~CreateChat()
{
    delete ui;
}
