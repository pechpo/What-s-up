#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCryptographicHash>
#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "director/director.h"

#include <QJsonArray>

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->MsgEdit->setReadOnly(true);
    chatId = 0;
    waiting = 0;
    dl = nullptr;
    settingsDialog = nullptr;

    connect(Director::getInstance(), &Director::r_chatHistory, this, &ChatWindow::slot_r_chatHistory);
    connect(Director::getInstance(), &Director::a_newMessage, this, &ChatWindow::slot_a_newMessage);
    connect(Director::getInstance(), &Director::r_send, this, &ChatWindow::slot_r_send);
    connect(Director::getInstance(), &Director::r_updateFile, this, &ChatWindow::slot_r_updateFile);

    switchChat(1);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

bool ChatWindow::isThisChat(const QJsonObject &obj) {
    if (!obj.value("chatId").isDouble()) {
        return false;
    }
    int recvId = obj.value("chatId").toInt();
    return (recvId == chatId);
}

void ChatWindow::switchChat(qint64 id) {
    if (id == chatId) {
        return ;
    }
    chatId = id;
    //ui->idLabel->setText("Chat ID: " + QString::number(id));
    ui->MsgEdit->setText("");
    QJsonObject msg;
    msg.insert("type", "q_chatHistory");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("count", 64);
    Director::getInstance()->sendJson(msg);
}

void ChatWindow::slot_r_chatHistory(const QJsonObject &obj) {
    if (!isThisChat(obj)) {
        return ;
    }
    if (!obj.value("chatHistory").isArray()) {
        return ;
    }
    ui->idLabel->setText("当前群聊：" + obj.value("name").toString());
    // todo: insert chatHistory message to proper place
    // current: reset
    QJsonArray recvHistory = obj.value("chatHistory").toArray();
    quint32 recvSize = recvHistory.size();
    history.clear();
    history.resize(recvSize);
    for (int i = 0; i < recvSize; i++) {
        history[i] = jsonToMessage(recvHistory.at(i).toObject());
    }
    updateText();
}

void ChatWindow::slot_a_newMessage(const QJsonObject &obj) {
    if (!isThisChat(obj)) {
        return ;
    }
    if (!obj.value("message").isObject()) {
        return ;
    }
    QJsonObject msg = obj.value("message").toObject();
    Message cur = jsonToMessage(msg);
    history.append(cur);
    //appendText(messageToString(cur));
    updateText();
}

ChatWindow::Message ChatWindow::jsonToMessage(const QJsonObject &obj) {
    Message cur;
    auto setIncompleteMessage = [] (Message &cur) -> void {
        cur.isSystem = true;
        cur.content = "Incomplete Message.";
    };
    if (!obj.value("senderId").isDouble()) {
        setIncompleteMessage(cur);
        return cur;
    }
    if (!obj.value("content").isString()) {
        setIncompleteMessage(cur);
        return cur;
    }
    //
    QString name = "Bot";
    if (obj.value("senderName").isString()) {
        name = obj.value("senderName").toString();
    }
    else {
        cur.isSystem = true;
    }
    cur.isSystem = false;
    cur.senderId = obj.value("senderId").toInt();
    //cur.senderName = "Carol" + QString::number(cur.senderId);
    cur.senderName = name;
    cur.content = obj.value("content").toString();
    return cur;
}

QString ChatWindow::messageToString(const Message &cur) {
    QString one;
    one.append(cur.senderName);
    if (cur.senderId > 0) {
        one.append(" (" + QString::number(cur.senderId) + ")");
    }
    one.append("\n" + cur.content + "\n");
    return one;
}

void ChatWindow::updateText() {
    // QVector<Message> history -> lineEdit->text()
    QString all;
    for (quint32 i = 0; i < history.size(); i++) {
        all.append(messageToString(history[i]) + "\n");
    }
    ui->MsgEdit->setPlainText(all);
    QTextCursor cursor = ui->MsgEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->MsgEdit->setTextCursor(cursor);
}

void ChatWindow::appendText(const QString &text) {
    ui->MsgEdit->insertPlainText(text + "\n");
    // outdated. do not use this.
}

void ChatWindow::on_sendButton_clicked()
{
   if (0 == waiting) {
        QJsonObject content;
        //content.insert("isPicture", false);
        content.insert("content", ui->inputEdit->toPlainText());
        QJsonObject msg;
        msg.insert("type", "e_send");
        msg.insert("chatId", QJsonValue(chatId));
        msg.insert("message", content);
        if (Director::getInstance()->sendJson(msg)) {
            waiting++;
        }
    }
}

void ChatWindow::slot_r_send(const QJsonObject &obj) {
    waiting--;
    if (!obj.value("success").isBool()) {
        return ;
    }
    if (true == obj.value("success").toBool()) {
        ui->inputEdit->setPlainText("");
        return ;
    }
}

void ChatWindow::on_fileButton_clicked() {
    if (0 == waiting) {
        QString str = QFileDialog::getOpenFileName(this, "Select File");
        if ("" == str) return;
        qDebug() << str;
        QFile file(str);
        if (!file.open(QIODevice::ReadOnly)){
            qDebug() << "failed to read file.";
            return;
        }
        QByteArray content = file.readAll();
        file.close();
        QString content_str = QString::fromUtf8(content.toBase64());  //redundent
        QFileInfo fileInfo(str);
        QJsonObject msg;
        msg.insert("type", "e_updateFile");
        msg.insert("chatId", QJsonValue(chatId));
        msg.insert("fileName", QJsonValue(fileInfo.fileName()));
        msg.insert("content", QJsonValue(content_str));
        if (Director::getInstance()->sendJson(msg)) {
            waiting++;
        }
    }
}

void ChatWindow::slot_r_updateFile(const QJsonObject &obj) {
    waiting--;
    if (!obj.value("success").isBool()) {
        return ;
    }
    if (true == obj.value("success").toBool()) {
        return ;
    }
}

void ChatWindow::on_pushButton_clicked()
{
    if (nullptr == dl){
        dl = new fileDownload();
        dl->set(chatId, &waiting, true);
    } else {
        if (true == dl->isVisible())
            dl->close();
        else{
            dl->set(chatId, &waiting, false);
        }
    }
}

void ChatWindow::on_settingsButton_clicked()
{
    if (nullptr != settingsDialog) {
        settingsDialog->close();
        delete settingsDialog;
    }
    settingsDialog = new ChatSettings(this, chatId);
    settingsDialog->clear();
    settingsDialog->show();
    //qDebug() << "successful click";
    QJsonObject msg;
    msg.insert("type", "q_chatInfo");
    msg.insert("chatId", QJsonValue(chatId));
    Director::getInstance()->sendJson(msg);
}

