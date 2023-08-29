#ifndef CREATECHAT_H
#define CREATECHAT_H

#include <QDialog>

namespace Ui {
class CreateChat;
}

class CreateChat : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChat(QWidget *parent = nullptr);
    ~CreateChat();
    void clear();
    void addChoice(quint32, const QString&);

private:
    Ui::CreateChat *ui;
};

#endif // CREATECHAT_H
