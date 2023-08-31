#include "photomessage.h"
#include "ui_photomessage.h"

photoMessage::photoMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoMessage)
{
    ui->setupUi(this);
}

photoMessage::~photoMessage()
{
    delete ui;
}

//request new photo
bool photoMessage::init(const ChatWindow::Message &obj, qint64 chatId, quint32 *wait) {
    if (chatId == 0) {
        return false;
    }
    path = QCoreApplication::applicationDirPath() + "/tmp/" + obj.content;
    QFile file(path);
    //if the photo exists, then no need to request the photo.
    if (file.exists()){
        show_photo();
        return true;
    }
    QJsonObject msg;
    msg.insert("type", "q_downloadFile");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("fileName", obj.content);
    fileName = obj.content;
    Director::getInstance()->sendJson(msg);
    connect(Director::getInstance(), &Director::r_downloadFile, this, &photoMessage::slot_receive_photo);
    waiting = wait;
    (*waiting)++;
    return true;
}

//after recieve the photo file, call this function to store file
bool photoMessage::slot_receive_photo(const QJsonObject &obj){
    //the photo should correspond to this message's filename.
    if (obj.value("fileName").toString() != fileName){
        return false;
    }
    path = QCoreApplication::applicationDirPath() + "/tmp/" + obj.value("fileName").toString();
    QFile file(path);
    //if the audio exists, then no need to store the audio.
    if (file.exists()){
        show_photo();
        return true;
    }
    if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "failed to write file.";
        return false;
    }
    file.write(QByteArray::fromBase64(obj.value("content").toString().toUtf8()));
    file.close();
    (*waiting)--;
    qDebug() << "slot_receive_photo_message";
    qDebug() << path;
    show_photo();
    return true;
}

void photoMessage::show_photo(){
    //show photo
    QImageReader reader(path);
    reader.setAutoTransform(true);
    const QImage img = reader.read();
    qDebug() << img.size();
    this->resize(img.size()/5);
    ui->photoLabel->resize(img.size()/5);
    ui->photoLabel->setPixmap(QPixmap(path));
    ui->photoLabel->setScaledContents(true);
}
