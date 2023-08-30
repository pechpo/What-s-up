#ifndef AUDIORECORD_H
#define AUDIORECORD_H

#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QAudioInput>
#include <QMediaRecorder>
#include <QWidget>
#include <QAudioDevice>
#include <QMediaFormat>
#include <QAudioSource>
#include <QUrl>
#include <QMediaPlayer>
#include <QMediaDevices>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QFile>
#include <QCryptographicHash>
#include "director/director.h"
#include <QFileInfo>
#include <QJsonValue>

namespace Ui {
class audioRecord;
}

class audioRecord : public QWidget
{
    Q_OBJECT

public:
    explicit audioRecord(QWidget*parent = nullptr);
    void set(qint64 id, quint32 *wait);
    ~audioRecord();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_listenButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::audioRecord *ui;
    QMediaCaptureSession *session;
    QAudioInput *audioInput;
    QMediaRecorder *recorder;
    QMediaFormat *format;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool isRecording;
    quint32 *waiting;
    qint64 chatId;
};

#endif // AUDIORECORD_H
