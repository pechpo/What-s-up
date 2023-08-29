#include "chatsettings.h"
#include "ui_chatsettings.h"

ChatSettings::ChatSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatSettings)
{
    ui->setupUi(this);

    settingsDialog = nullptr;
}

ChatSettings::~ChatSettings()
{
    delete ui;
}
