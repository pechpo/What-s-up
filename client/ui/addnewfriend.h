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
    void setId(quint32 newId);
    void setName(const QString&);
    void setAvatar(const QString&);

private slots:
    void on_acceptButton_clicked();

    void on_declineButton_clicked();

private:
    Ui::AddNewFriend *ui;
    ProfileBar *bar;
    qint64 id;
};

#endif // ADDNEWFRIEND_H
