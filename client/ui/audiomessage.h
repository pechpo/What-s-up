#ifndef AUDIOMESSAGE_H
#define AUDIOMESSAGE_H

#include <QWidget>
#include <QJsonObject>
#include <QFile>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>

namespace Ui {
class audioMessage;
}

class audioMessage : public QWidget
{
    Q_OBJECT

public:
    explicit audioMessage(QWidget *parent = nullptr);
    bool init(const QJsonObject &obj);
    ~audioMessage();

public slots:
    void slot_StatusChange(QMediaPlayer::MediaStatus status);

private slots:
    void on_pushButton_clicked();

private:
    Ui::audioMessage *ui;
    bool isPlaying;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString path;
};

#endif // AUDIOMESSAGE_H
