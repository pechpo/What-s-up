#include "audiorecord.h"
#include "ui_audiorecord.h"

audioRecord::audioRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::audioRecord)
{
    ui->setupUi(this);
    session = nullptr;
    audioInput = nullptr;
    recorder = nullptr;
    format = nullptr;
    isRecording = false;
    player = nullptr;
    audioOutput = nullptr;
    connect(Director::getInstance(), &Director::r_updateFile, this, &audioRecord::slot_r_updateFile);
}

audioRecord::~audioRecord()
{
    delete ui;
}

void audioRecord::set(qint64 *id, quint32 *wait) {
    chatId = id;
    waiting = wait;
}

void audioRecord::on_startButton_clicked()
{

    if (nullptr != session) {
        delete session;
        delete audioInput;
        delete recorder;
        delete format;
    }
    session = new QMediaCaptureSession;
    audioInput = new QAudioInput;
    recorder = new QMediaRecorder;
    const QAudioDevice &inputDevice = QMediaDevices::defaultAudioInput();
    audioInput->setDevice(inputDevice);
    session->setAudioInput(audioInput);
    session->setRecorder(recorder);
    recorder->setQuality(QMediaRecorder::HighQuality);
    format = new QMediaFormat;
    format->setAudioCodec(QMediaFormat::AudioCodec::MP3);
    format->setFileFormat(QMediaFormat::MP3);
    recorder->setMediaFormat(*format);
    QString path = QCoreApplication::applicationDirPath();
    recorder->setOutputLocation(QUrl::fromLocalFile(path + "/tmp/tmp_audio"));
    recorder->record();
    ui->statusList->addItem(QString("Start recording..."));
    isRecording = true;
}

void audioRecord::on_stopButton_clicked()
{
    if (nullptr == session) {
        return ;
    }
    recorder->stop();
    ui->statusList->addItem(QString("Stop recording..."));
    isRecording = false;
}


void audioRecord::on_listenButton_clicked()
{
    if (true == isRecording) {
        ui->statusList->addItem(QString("Still recording! Please stop recording first."));
        return ;
    }
    //replay the recorded audio
    if (nullptr != player) {
        delete player;
        delete audioOutput;
    }
    QString path = QCoreApplication::applicationDirPath() + "/tmp/tmp_audio.m4a";
    QFile File(path);
    if (!File.exists()) {
        ui->statusList->addItem(QString("Record file does not exist!"));
        return ;
    }
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    const QAudioDevice &outputDevice = QMediaDevices::defaultAudioOutput();
    audioOutput->setDevice(outputDevice);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile(path));
    audioOutput->setVolume(50);
    player->play();
    ui->statusList->addItem(QString("Start replaying..."));
}


void audioRecord::on_sendButton_clicked()
{
    QString path = QCoreApplication::applicationDirPath() + "/tmp/tmp_audio.m4a";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "failed to read file.";
        return;
    }
    QByteArray content = file.readAll();
    file.close();
    QString content_str = QString::fromUtf8(content.toBase64());  //redundent
    QString MD5 = QCryptographicHash::hash(content, QCryptographicHash::Md5).toHex();
    QJsonObject msg;
    msg.insert("type", "e_updateFile");
    msg.insert("chatId", QJsonValue(*chatId));
    msg.insert("fileName", QJsonValue(MD5 + ".m4a"));
    msg.insert("content", QJsonValue(content_str));
    msg.insert("format", QJsonValue("audio"));
    if (Director::getInstance()->sendJson(msg)) {
        (*waiting)++;
    }
    ui->statusList->addItem(QString("Sending audio..."));
}

void audioRecord::slot_r_updateFile(const QJsonObject&)
{
    ui->statusList->addItem(QString("Success."));
}
