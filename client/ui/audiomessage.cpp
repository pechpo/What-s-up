#include "audiomessage.h"
#include "ui_audiomessage.h"

audioMessage::audioMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::audioMessage)
{
    ui->setupUi(this);
}

audioMessage::~audioMessage()
{
    delete ui;
}

//after recieve the audio file, call this function to store file
bool audioMessage::init(const QJsonObject &obj) {
    path = QCoreApplication::applicationDirPath() + "/tmp/" + obj.value("fileName").toString();
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "failed to write file.";
        return false;
    }
    file.write(QByteArray::fromBase64(obj.value("content").toString().toUtf8()));
    file.close();
    //(*waiting)--;
    return true;
}

void audioMessage::on_pushButton_clicked()
{
    if (!isPlaying){
        isPlaying = true;
        ui->pushButton->setIcon(QIcon(":/images/image/stop.png"));
        if (nullptr != player) {
            delete player;
            delete audioOutput;
        }
        player = new QMediaPlayer;
        audioOutput = new QAudioOutput;
        const QAudioDevice &outputDevice = QMediaDevices::defaultAudioOutput();
        audioOutput->setDevice(outputDevice);
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(path));
        audioOutput->setVolume(50);
        player->play();
        connect(player, &QMediaPlayer::mediaStatusChanged, this, &audioMessage::slot_StatusChange);
    } else {
        isPlaying = false;
        ui->pushButton->setIcon(QIcon(":/images/image/play.png"));
        player->stop();
    }
}

//When the audio come to the end
void audioMessage::slot_StatusChange(QMediaPlayer::MediaStatus status)
{
    if (QMediaPlayer::MediaStatus::EndOfMedia != status){
        return ;
    }
    isPlaying = false;
    ui->pushButton->setIcon(QIcon(":/images/image/stop.png"));
}

