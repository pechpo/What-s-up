#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class Registerdialog;
}

class Registerdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Registerdialog(QWidget *parent = nullptr);
    ~Registerdialog();


private slots:
    void on_registerBtn_clicked();

private:
    Ui::Registerdialog *ui;
};

#endif // REGISTERDIALOG_H
