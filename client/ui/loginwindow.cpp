#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "director/director.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(Director::getInstance(), &Director::receiveTestString, this, &LoginWindow::on_receiveTestString);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_receiveTestString(const QString &text) {
    ui->receivedText->insertPlainText("recv: " + text + "\n");
}

void LoginWindow::on_connectButton_clicked()
{
    QString serverIP = ui->hostInput->text();
    quint16 serverPort = ui->portInput->text().toInt();
    Director::getInstance()->connectServer(serverIP, serverPort);
}

void LoginWindow::on_sendButton_clicked()
{
    QString text = ui->sendInput->text();
    Director::getInstance()->sendPureMessage(text);
}

