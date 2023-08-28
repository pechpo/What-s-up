#ifndef ADDNEWFRIEND_H
#define ADDNEWFRIEND_H

#include <QWidget>
#include "profilebar.h"

namespace Ui {
class AddNewFriend;
}

class AddNewFriend : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewFriend(QWidget *parent = nullptr);
    ~AddNewFriend();
    void setName(const QString&);
    void setId(quint32 newId);

private:
    Ui::AddNewFriend *ui;
    ProfileBar *bar;
    quint32 id;
};

#endif // ADDNEWFRIEND_H
