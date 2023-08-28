#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
//    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    ui->setupUi(this);

    snf = nullptr;

    cw = new ChatWindow(this);
    cw->move(250, 50);
    cw->show();

    ui->closeButton->setVisible(false);
    ui->minimizeButton->setVisible(false);


    //for (quint16 i = 0; i < 50; i++)
    //    cw->appendText("Hello, world" + QString::number(i));
}

mainWindow::~mainWindow()
{
    delete snf;
    delete ui;
}

void mainWindow::on_closeButton_clicked()
{
    close();
}


void mainWindow::on_minimizeButton_clicked()
{
    showMinimized();
}


void mainWindow::on_addnewfriendButton_clicked()
{
    if (nullptr == snf) {
        snf = new SearchNewFriend();
        snf->show();
    }
    else {
        snf->close();
        snf->show();
    }
}

