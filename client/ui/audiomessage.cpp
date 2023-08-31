#include "audiomessage.h"
#include "ui_audiomessage.h"

audioMessage::audioMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::audioMessage)
{
    ui->setupUi(this);
    player = nullptr;
    audioOutput = nullptr;
    ui->pushButton->setIcon(QIcon(":/images/image/play.png"));
}

audioMessage::~audioMessage()
{
    delete ui;
}

//request new audio file
bool audioMessage::init(const ChatWindow::Message &obj, qint64 chatId, quint32 *wait) {
    if (chatId == 0) {
        return false;
    }
    QJsonObject msg;
    msg.insert("type", "q_downloadFile");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("fileName", obj.content);
    fileName = obj.content;
    Director::getInstance()->sendJson(msg);
    connect(Director::getInstance(), &Director::r_downloadFile, this, &audioMessage::slot_receive_audio);
    waiting = wait;
    (*waiting)++;
    return true;
}

//after recieve the audio file, call this function to store file
bool audioMessage::slot_receive_audio(const QJsonObject &obj){
    //the audio should correspond to this message's filename.
    if (obj.value("fileName").toString() != fileName){
        return false;
    }
    path = QCoreApplication::applicationDirPath() + "/tmp/" + obj.value("fileName").toString();
    QFile file(path);
    //if the audio exists, then no need to store the audio.
    if (file.exists()){
        return false;
    }
    if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "failed to write file.";
        return false;
    }
    file.write(QByteArray::fromBase64(obj.value("content").toString().toUtf8()));
    file.close();
    (*waiting)--;
    qDebug() << "slot_receive_audio_message";
    qDebug() << path;

    //get audio length
    player = new QMediaPlayer;
    player->setSource(QUrl::fromLocalFile(path));
    qint64 time = player->metaData()[QMediaMetaData::Duration].toInt();
    if (time != 0)
        ui->label->setText(QString("%1s").arg(time / 1000.0));
    return true;
}

void audioMessage::on_pushButton_clicked()
{
    if (!isPlaying){
        isPlaying = true;
        ui->pushButton->setIcon(QIcon(":/images/image/stop.png"));
        if (nullptr != player) {
            delete player;
        }
        if (nullptr != audioOutput) {
            delete audioOutput;
        }
        player = new QMediaPlayer;
        audioOutput = new QAudioOutput;
        const QAudioDevice &outputDevice = QMediaDevices::defaultAudioOutput();
        audioOutput->setDevice(outputDevice);
        player->setAudioOutput(audioOutput);
        qDebug() << "start playing";
        qDebug() << path;
        player->setSource(QUrl::fromLocalFile(path));
        audioOutput->setVolume(50);
        player->play();
    } else {
        isPlaying = false;
        ui->pushButton->setIcon(QIcon(":/images/image/play.png"));
        player->stop();
    }
}

void audioMessage::slot_StatusChange(QMediaPlayer::MediaStatus status)
{
    if (QMediaPlayer::MediaStatus::EndOfMedia != status){
        return ;
    }
    isPlaying = false;
    ui->pushButton->setIcon(QIcon(":/images/image/play.png"));
}
