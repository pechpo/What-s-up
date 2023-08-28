#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "director/director.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    this->setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    connect(Director::getInstance(), &Director::receiveTestString, this, &LoginWindow::on_receiveTestString);

    ui->closeButton->setVisible(false);
    ui->minimizeButton->setVisible(false);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_receiveTestString(const QString &text) {
    ui->receivedText->insertPlainText(text + "\n");
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



void LoginWindow::on_closeButton_clicked()
{
    close();
}


void LoginWindow::on_minimizeButton_clicked()
{
    showMinimized();
}

