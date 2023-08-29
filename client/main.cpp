#include "ui/loginwindow.h"
#include "ui/logindialog.h"
#include "ui/mainwindow.h"
#include "ui/chatwindow.h"
#include "ui/profilebar.h"
#include "ui/searchnewfriend.h"
#include "director/director.h"
#include "ui/createchat.h"

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
<<<<<<< HEAD
    mainWindow mw;
    CreateChat cc;
    //ProfileBar pb;
    LoginDialog d;
    d.show();
    mw.show();
    cc.show();
=======
    //mainWindow mw;
    //ProfileBar pb;
    LoginDialog d;
    d.show();
    //mw.show();
>>>>>>> ca9bf9dadf6f661fea8456d072b1a16c8e9313d6
    //pb.show();
    //cw.show();
    return a.exec();
}
