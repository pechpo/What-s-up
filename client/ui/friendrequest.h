#ifndef FRIENDREQUEST_H
#define FRIENDREQUEST_H

#include <QWidget>
#include <QJsonObject>
#include "profilebar.h"

namespace Ui {
class FriendRequest;
}

class FriendRequest : public QWidget
{
    Q_OBJECT

public:
    explicit FriendRequest(QWidget *parent = nullptr);
    ~FriendRequest();
    void setId(quint32 newId);
    void setName(const QString&);
    void setAvatar(const QString&);

public slots:
    void slot_r_addFriend(const QJsonObject&);

private slots:
    void on_requestButton_clicked();

private:
    Ui::FriendRequest *ui;
    ProfileBar *bar;
    qint64 id;
    bool alreadySend;
};

#endif // FRIENDREQUEST_H
