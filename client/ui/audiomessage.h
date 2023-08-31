#ifndef AUDIOMESSAGE_H
#define AUDIOMESSAGE_H

#include <QWidget>
#include <QJsonObject>
#include <QFile>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include "chatwindow.h"

namespace Ui {
class audioMessage;
}

class audioMessage : public QWidget
{
    Q_OBJECT

public:
    explicit audioMessage(QWidget *parent = nullptr);
    bool init(const ChatWindow::Message &obj, qint64 chatId, quint32 *wait);
    ~audioMessage();

public slots:
    bool slot_receive_audio(const QJsonObject &obj);
    void slot_StatusChange(QMediaPlayer::MediaStatus status);

private slots:
    void on_pushButton_clicked();

private:
    Ui::audioMessage *ui;
    bool isPlaying;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString path;
    quint32 *waiting;
    QString fileName;
};

#endif // AUDIOMESSAGE_H
