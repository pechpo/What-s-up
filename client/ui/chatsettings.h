#ifndef CHATSETTINGS_H
#define CHATSETTINGS_H

#include <QDialog>
#include "friendrequest.h"

namespace Ui {
class ChatSettings;
}

class ChatSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ChatSettings(QWidget *parent = nullptr, qint64 id = 0);
    ~ChatSettings();
    void clear();

public slots:
    void slot_r_chatInfo(const QJsonObject&);
    void slot_r_editChatInfo(const QJsonObject&);
    void slot_r_exitChat(const QJsonObject&);

private slots:
    void on_confirmButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::ChatSettings *ui;
    qint64 chatId;
    QVector<FriendRequest*> userList;
};

#endif // CHATSETTINGS_H
