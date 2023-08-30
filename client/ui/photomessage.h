#ifndef PHOTOMESSAGE_H
#define PHOTOMESSAGE_H

#include <QWidget>

namespace Ui {
class photoMessage;
}

class photoMessage : public QWidget
{
    Q_OBJECT

public:
    explicit photoMessage(QWidget *parent = nullptr);
    ~photoMessage();

private:
    Ui::photoMessage *ui;
};

#endif // PHOTOMESSAGE_H
