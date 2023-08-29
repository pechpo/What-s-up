#ifndef CREATECHAT_H
#define CREATECHAT_H

#include <QWidget>

namespace Ui {
class CreateChat;
}

class CreateChat : public QWidget
{
    Q_OBJECT

public:
    explicit CreateChat(QWidget *parent = nullptr);
    ~CreateChat();

private:
    Ui::CreateChat *ui;
};

#endif // CREATECHAT_H
