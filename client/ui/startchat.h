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

private:
    Ui::StartChat *ui;
    ProfileBar *bar;
    quint32 id;
};

#endif // STARTCHAT_H
