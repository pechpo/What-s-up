#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QWidget>

namespace Ui {
class GroupList;
}

class GroupList : public QWidget
{
    Q_OBJECT

public:
    explicit GroupList(QWidget *parent = nullptr);
    ~GroupList();

private:
    Ui::GroupList *ui;
};

#endif // GROUPLIST_H
