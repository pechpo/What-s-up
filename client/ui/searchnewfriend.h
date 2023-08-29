#ifndef SEARCHNEWFRIEND_H
#define SEARCHNEWFRIEND_H

#include <QWidget>
#include <QJsonObject>

#include "profilebar.h"
#include "director/director.h"

namespace Ui {
class SearchNewFriend;
}

class SearchNewFriend : public QWidget
{
    Q_OBJECT

public:
    explicit SearchNewFriend(QWidget *parent = nullptr);
    ~SearchNewFriend();
    void clear();

public slots:
    void slot_r_userInfo(const QJsonObject&);
    void slot_r_chatInfo(const QJsonObject&);
    void slot_r_addFriend(const QJsonObject&);
    void slot_r_joinChat(const QJsonObject&);

private slots:
    void on_SearchButton_clicked();

    void on_confirmButton_clicked();

    void on_switchButton_clicked();

private:
    Ui::SearchNewFriend *ui;
    ProfileBar *bar;
    qint64 userId;
    quint32 waiting;
    enum Director::State curState;
};

#endif // SEARCHNEWFRIEND_H
