#include "avatarcreator.h"

#include <QFile>
#include <QDebug>

QString AvatarCreator::prefix = ":/images/image/Avatars/";
AvatarCreator::AvatarCreator()
{
    cnt = 0;
    while (true) {
        QString filePath = prefix + "A" + QString::number(cnt + 1) + ".WEBP";
        QFile file(filePath);
        if (!file.exists()) {
            break ;
        }
        cnt++;
    }
    //qDebug() << cnt;
}

QString AvatarCreator::stringToPath(const QString &avatar) {
    // stupid.
    QByteArray arr = avatar.toLatin1();
    quint32 val = 0;
    for (quint32 i = 0; i < arr.size(); i++) {
        val += arr.at(i);
    }
    val = (val % cnt) + 1;
    QString res = prefix + "A" + QString::number(val) + ".WEBP";
    return res;
}
