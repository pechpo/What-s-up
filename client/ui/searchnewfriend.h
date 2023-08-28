#ifndef SEARCHNEWFRIEND_H
#define SEARCHNEWFRIEND_H

#include <QWidget>

namespace Ui {
class SearchNewFriend;
}

class SearchNewFriend : public QWidget
{
    Q_OBJECT

public:
    explicit SearchNewFriend(QWidget *parent = nullptr);
    ~SearchNewFriend();

private:
    Ui::SearchNewFriend *ui;
};

#endif // SEARCHNEWFRIEND_H
