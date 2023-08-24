#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "registerdialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::on_loginBtn_clicked() {
    // 判断用户名和密码是否正确，如果错误则弹出警告对话框
    QString sql = QString("select *from user;");
    QSqlQuery *sqlQuery = new QSqlQuery("user");

    int flag = 0;

    if(sqlQuery->exec(sql)) {
        //遍历查询到的所有数据
        while (sqlQuery->next()) {
            QString usr, pwd;
            usr = sqlQuery->value("usr").toString();
            pwd = sqlQuery->value("pwd").toString();
            if (usr == ui->usrLineEdit->text().trimmed() && pwd == ui->pwdLineEdit->text()) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) {
        QMessageBox::information(NULL, tr("Note"), tr("Login success!"));
        accept();
    }
    else {
        QMessageBox::warning(this, tr("Waring"), tr("User name or Password error!"), QMessageBox::Yes);
        // 清空内容并定位光标
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}


void LoginDialog::on_registerBtn_clicked() {
    Registerdialog *registerdialog = new Registerdialog(this);
    registerdialog->show();
}

