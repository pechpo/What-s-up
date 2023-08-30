#include "ui/logindialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //Director::getInstance()->toMainWindow();
    //ChatWindow cw;
    //mainWindow mw;
    //ProfileBar pb;
    LoginDialog *d = new LoginDialog();  //login dialog window
    d->show();
    //mw.show();
    //mainWindow mw;
    //ProfileBar pb;
//    LoginDialog d;
//    d.show();
    //mw.show();
    //pb.show();
    //cw.show();
    return a.exec();
}
