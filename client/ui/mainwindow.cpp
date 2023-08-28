#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    this->setAttribute(Qt::WA_TranslucentBackground);      //把初始的 dialog 窗口设置为透明的
    ui->setupUi(this);
    cw = new ChatWindow(this);
    cw->move(160, 41);
    cw->show();
}

mainWindow::~mainWindow()
{
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

