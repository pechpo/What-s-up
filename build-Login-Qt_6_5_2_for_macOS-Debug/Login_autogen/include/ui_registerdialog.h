/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Registerdialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit;
    QLineEdit *pwdConfirmLineEdit_2;
    QPushButton *registerBtn;
    QPushButton *returnBtn;

    void setupUi(QDialog *Registerdialog)
    {
        if (Registerdialog->objectName().isEmpty())
            Registerdialog->setObjectName("Registerdialog");
        Registerdialog->resize(400, 300);
        label = new QLabel(Registerdialog);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 20, 211, 51));
        QFont font;
        font.setPointSize(36);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Registerdialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 90, 71, 21));
        label_3 = new QLabel(Registerdialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 140, 71, 21));
        label_4 = new QLabel(Registerdialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 190, 71, 21));
        usrLineEdit = new QLineEdit(Registerdialog);
        usrLineEdit->setObjectName("usrLineEdit");
        usrLineEdit->setGeometry(QRect(140, 90, 191, 25));
        usrLineEdit->setEchoMode(QLineEdit::Normal);
        pwdLineEdit = new QLineEdit(Registerdialog);
        pwdLineEdit->setObjectName("pwdLineEdit");
        pwdLineEdit->setGeometry(QRect(140, 140, 191, 25));
        pwdLineEdit->setEchoMode(QLineEdit::Password);
        pwdConfirmLineEdit_2 = new QLineEdit(Registerdialog);
        pwdConfirmLineEdit_2->setObjectName("pwdConfirmLineEdit_2");
        pwdConfirmLineEdit_2->setGeometry(QRect(140, 190, 191, 25));
        pwdConfirmLineEdit_2->setEchoMode(QLineEdit::Password);
        registerBtn = new QPushButton(Registerdialog);
        registerBtn->setObjectName("registerBtn");
        registerBtn->setGeometry(QRect(220, 240, 101, 31));
        returnBtn = new QPushButton(Registerdialog);
        returnBtn->setObjectName("returnBtn");
        returnBtn->setGeometry(QRect(70, 240, 101, 31));

        retranslateUi(Registerdialog);
        QObject::connect(returnBtn, &QPushButton::clicked, Registerdialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(Registerdialog);
    } // setupUi

    void retranslateUi(QDialog *Registerdialog)
    {
        Registerdialog->setWindowTitle(QCoreApplication::translate("Registerdialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Registerdialog", "\346\263\250\345\206\214", nullptr));
        label_2->setText(QCoreApplication::translate("Registerdialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("Registerdialog", "\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("Registerdialog", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        usrLineEdit->setPlaceholderText(QCoreApplication::translate("Registerdialog", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        pwdLineEdit->setPlaceholderText(QCoreApplication::translate("Registerdialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        pwdConfirmLineEdit_2->setPlaceholderText(QCoreApplication::translate("Registerdialog", "\350\257\267\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        registerBtn->setText(QCoreApplication::translate("Registerdialog", "\346\263\250\345\206\214", nullptr));
        returnBtn->setText(QCoreApplication::translate("Registerdialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registerdialog: public Ui_Registerdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
