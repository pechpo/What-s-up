#ifndef SEARCHNEWFRIEND_H
#define SEARCHNEWFRIEND_H

#include <QWidget>
#include <QJsonObject>

#include "profilebar.h"

namespace Ui {
class SearchNewFriend;
}

class SearchNewFriend : public QWidget
{
    Q_OBJECT

public:
    explicit SearchNewFriend(QWidget *parent = nullptr);
    ~SearchNewFriend();

public slots:
    void slot_r_userInfo(const QJsonObject&);

private slots:
    void on_SearchButton_clicked();

private:
    Ui::SearchNewFriend *ui;
    ProfileBar *bar;
    qint64 userId;
    quint32 waiting;
};

#endif // SEARCHNEWFRIEND_H
