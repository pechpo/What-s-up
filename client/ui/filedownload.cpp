#include "director/director.h"
#include "filedownload.h"
#include "ui_filedownload.h"
#include <qjsonarray.h>

fileDownload::fileDownload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileDownload)
{
    ui->setupUi(this);
}

fileDownload::~fileDownload()
{
    delete ui;
}

void fileDownload::set(qint64 chatId, quint32 &waiting){
    QJsonObject msg;
    msg.insert("type", "q_list_filesInChat");
    msg.insert("chatId", QJsonValue(chatId));
    if (Director::getInstance()->sendJson(msg)) {
        waiting++;
    }
    connect(Director::getInstance(), &Director::r_list_filesInChat, this, &fileDownload::slot_r_list_filesInChat);
}


void fileDownload::slot_r_list_filesInChat(const QJsonObject &obj) {
    QJsonArray recvHistory = obj.value("files").toArray();
    quint32 recvSize = recvHistory.size();
    for (int i = 0; i < recvSize; i++) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString("111"));
        ui->fileList->addItem(item);
    }
    this->show();
}
