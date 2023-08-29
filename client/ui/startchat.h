#ifndef STARTCHAT_H
#define STARTCHAT_H

#include <QWidget>
#include "profilebar.h"

namespace Ui {
class StartChat;
}

class StartChat : public QWidget
{
    Q_OBJECT

public:
    explicit StartChat(QWidget *parent = nullptr);
    ~StartChat();
    void setName(const QString&);
    void setId(quint32 newId);
    void setAvatar(const QString&);
    qint64 getId();
    QString getName();

private slots:
    void on_chatButton_clicked();

private:
    Ui::StartChat *ui;
    ProfileBar *bar;
    qint64 id;
};

#endif // STARTCHAT_H
