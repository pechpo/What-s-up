#ifndef ADDNEWFRIEND_H
#define ADDNEWFRIEND_H

#include <QWidget>

namespace Ui {
class AddNewFriend;
}

class AddNewFriend : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewFriend(QWidget *parent = nullptr);
    ~AddNewFriend();

private:
    Ui::AddNewFriend *ui;
};

#endif // ADDNEWFRIEND_H
