#include "createchat.h"
#include "ui_createchat.h"

CreateChat::CreateChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);
}

CreateChat::~CreateChat()
{
    delete ui;
}

void CreateChat::clear() {

}

void CreateChat::addChoice(quint32 id, const QString &name) {

}
