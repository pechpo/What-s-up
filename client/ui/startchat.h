#ifndef STARTCHAT_H
#define STARTCHAT_H

#include <QWidget>

namespace Ui {
class StartChat;
}

class StartChat : public QWidget
{
    Q_OBJECT

public:
    explicit StartChat(QWidget *parent = nullptr);
    ~StartChat();

private:
    Ui::StartChat *ui;
};

#endif // STARTCHAT_H
