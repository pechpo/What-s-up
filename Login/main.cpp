#include <QApplication>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "mainwindow.h"
#include "logindialog.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("/Users/foreverlasting/git/What-s-up/Login/account.db");
    database.setUserName("root");
    database.setPassword("123456");
    database.open();
    MainWindow w;
    LoginDialog dlg;
    if (dlg.exec() == QDialog::Accepted) {
        w.show();
        database.close();
        return a.exec();
    }
    else {
        database.close();
        return 0;
    }
}
