#include "chatsettings.h"
#include "ui_chatsettings.h"
#include "director/director.h"

ChatSettings::ChatSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatSettings)
{
    ui->setupUi(this);
}

ChatSettings::~ChatSettings()
{
    delete ui;
}

void ChatSettings::on_confirmButton_clicked()
{

}

