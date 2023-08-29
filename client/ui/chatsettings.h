#ifndef CHATSETTINGS_H
#define CHATSETTINGS_H

#include <QDialog>

namespace Ui {
class ChatSettings;
}

class ChatSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ChatSettings(QWidget *parent = nullptr);
    ~ChatSettings();

private:
    Ui::ChatSettings *ui;
};

#endif // CHATSETTINGS_H
