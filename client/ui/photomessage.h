#ifndef PHOTOMESSAGE_H
#define PHOTOMESSAGE_H

#include <QWidget>
#include "chatwindow.h"
#include <QImage>
#include <QImageReader>

namespace Ui {
class photoMessage;
}

class photoMessage : public QWidget
{
    Q_OBJECT

public:
    explicit photoMessage(QWidget *parent = nullptr);
    bool init(const ChatWindow::Message &obj, qint64 chatId, quint32 *wait);
    void show_photo();
    ~photoMessage();

public slots:
    bool slot_receive_photo(const QJsonObject &obj);

private:
    Ui::photoMessage *ui;
    quint32 *waiting;
    QString fileName;
    QString path;
};

#endif // PHOTOMESSAGE_H
