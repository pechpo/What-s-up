/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *loginBtn;
    QPushButton *exitBtn;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 300);
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 80, 71, 21));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 150, 71, 21));
        usrLineEdit = new QLineEdit(LoginDialog);
        usrLineEdit->setObjectName("usrLineEdit");
        usrLineEdit->setGeometry(QRect(130, 80, 191, 25));
        usrLineEdit->setEchoMode(QLineEdit::Normal);
        pwdLineEdit = new QLineEdit(LoginDialog);
        pwdLineEdit->setObjectName("pwdLineEdit");
        pwdLineEdit->setGeometry(QRect(130, 150, 191, 25));
        pwdLineEdit->setEchoMode(QLineEdit::Password);
        loginBtn = new QPushButton(LoginDialog);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setGeometry(QRect(230, 220, 89, 25));
        exitBtn = new QPushButton(LoginDialog);
        exitBtn->setObjectName("exitBtn");
        exitBtn->setGeometry(QRect(60, 220, 89, 25));

        retranslateUi(LoginDialog);
        QObject::connect(exitBtn, &QPushButton::clicked, LoginDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        usrLineEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        pwdLineEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        loginBtn->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        exitBtn->setText(QCoreApplication::translate("LoginDialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
