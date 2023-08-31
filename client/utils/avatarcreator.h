#ifndef AVATARCREATOR_H
#define AVATARCREATOR_H

#include <QString>

class AvatarCreator
{
public:
    AvatarCreator();
    QString stringToPath(const QString&);
private:
    quint32 cnt;
    static QString prefix;
};

#endif // AVATARCREATOR_H
