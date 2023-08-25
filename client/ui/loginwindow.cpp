#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "director/director.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_connectButton_clicked()
{
    QString serverIP = ui->hostInput->text();
    quint16 serverPort = ui->portInput->text().toInt();
    Director::getInstance()->connectServer(serverIP, serverPort);
}
