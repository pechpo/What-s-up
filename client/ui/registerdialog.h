#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

public slots:
    void slot_r_register(const QJsonObject&);

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::RegisterDialog *ui;
    quint32 waiting;
};

#endif // REGISTERDIALOG_H
