#include <QFile>
#include <QFileDialog>
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

void fileDownload::set(qint64 Id, quint32 *wait, bool init){

    //clear the list
    int n=ui->fileList->count();
    for(int i=0; i<n; i++) {
        QListWidgetItem *item = ui->fileList->takeItem(0);
        delete item;
    }
    for(int i=0; i<n; i++) {
        QListWidgetItem *item = ui->senderList->takeItem(0);
        delete item;
    }

    //send json
    chatId = Id;
    waiting = wait;
    QJsonObject msg;
    msg.insert("type", "q_list_filesInChat");
    msg.insert("chatId", QJsonValue(chatId));
    if (Director::getInstance()->sendJson(msg)) {
        waiting++;
    }
    if (init) connect(Director::getInstance(), &Director::r_list_filesInChat, this, &fileDownload::slot_r_list_filesInChat);
}


void fileDownload::slot_r_list_filesInChat(const QJsonObject &obj) {
    QJsonArray recvHistory = obj.value("files").toArray();
    quint32 recvSize = recvHistory.size();
    for (int i = 0; i < recvSize; i++) {
        QListWidgetItem *item = new QListWidgetItem;
        QJsonObject tmp = recvHistory[i].toObject();
        item->setText(tmp["name"].toString());
        ui->fileList->addItem(item);
        QListWidgetItem *item2 = new QListWidgetItem;
        item2->setText(tmp["senderName"].toString());
        ui->senderList->addItem(item2);
    }
    this->show();
    waiting--;
}

void fileDownload::on_Download_clicked()
{
    if (0 == ui->fileList->selectedItems().size()) {
        return ;
    }
    QJsonObject msg;
    msg.insert("type", "q_downloadFile");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("fileName", ui->fileList->selectedItems()[0]->text());
    if (Director::getInstance()->sendJson(msg)) {
        waiting++;
    }
    connect(Director::getInstance(), &Director::r_downloadFile, this, &fileDownload::slot_r_downloadFile);
}

void fileDownload::slot_r_downloadFile(const QJsonObject &obj) {
    QString str = QFileDialog::getSaveFileName(this, "Select download path", "~/"+obj.value("fileName").toString());
    if ("" == str) return;
    QFile file(str);
    if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "failed to write file.";
        return;
    }
    file.write(QByteArray::fromBase64(obj.value("content").toString().toUtf8()));
    file.close();
    waiting--;
}
