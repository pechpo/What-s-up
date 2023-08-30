#include "photomessage.h"
#include "ui_photomessage.h"

photoMessage::photoMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoMessage)
{
    ui->setupUi(this);
}

photoMessage::~photoMessage()
{
    delete ui;
}
