#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include <iostream>

Registerdialog::Registerdialog(QWidget *parent) : QDialog(parent), ui(new Ui::Registerdialog) {
    ui->setupUi(this);
}

Registerdialog::~Registerdialog() {
    delete ui;
}

void Registerdialog::on_registerBtn_clicked() {
    //在此处添加数据传入数据库的代码
    QString usr = ui->usrLineEdit->text().trimmed();
    QString pwd = ui->pwdLineEdit->text();
    QSqlQuery *sqlQuery = new QSqlQuery("user");
    if (pwd != ui->pwdConfirmLineEdit_2->text()) {
        QMessageBox::warning(this, tr("Waring"), tr("Password wrong!"), QMessageBox::Yes);
        // 清空内容并定位光标
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
    else {
        QString sql = QString("insert into user(usr, pwd) values('%1', '%2');").arg(usr).arg(pwd);
        if (sqlQuery->exec(sql)) {
        }
        else {
        }
    }
    close();
}

