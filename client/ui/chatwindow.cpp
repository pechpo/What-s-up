#include <QCryptographicHash>
#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "audiomessage.h"
#include "photomessage.h"
#include "director/director.h"
#include <QMessageBox>
#include <QScrollBar>

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->MsgEdit->setReadOnly(true);
    ui->scrollArea->setWidgetResizable(false);
    chatId = 0;
    waiting = 0;
    dl = nullptr;
    ar = nullptr;
    settingsDialog = nullptr;
    QString sendstyle = R"(
        QPushButton {
            border: none;
            background-color: rgba(59, 180, 193, 0.75);
            border-radius:10px;
        }
        QPushButton:hover {
            background-color: rgba(59, 180, 193, 1);
        }
    )";
    ui->sendButton->setStyleSheet(sendstyle);
    messages.clear();
    ui->fileButton->setToolTip(tr("上传文件"));
    ui->settingsButton->setToolTip(tr("群聊信息设置"));
    ui->pushButton->setToolTip(tr("下载文件"));
    ui->audioButton->setToolTip("发送语音");
    ui->photoButton->setToolTip("上传照片");

    connect(Director::getInstance(), &Director::r_chatHistory, this, &ChatWindow::slot_r_chatHistory);
    connect(Director::getInstance(), &Director::a_newMessage, this, &ChatWindow::slot_a_newMessage);
    connect(Director::getInstance(), &Director::r_send, this, &ChatWindow::slot_r_send);
    connect(Director::getInstance(), &Director::r_updateFile, this, &ChatWindow::slot_r_updateFile);
    connect(Director::getInstance(), &Director::r_talk, this, &ChatWindow::slot_r_talk);

    switchChat(0);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

qint64 ChatWindow::recvChatId(const QJsonObject &obj) {
    if (!obj.value("chatId").isDouble()) {
        return 0;
    }
    int recvId = obj.value("chatId").toInt();
    return recvId;
}

void ChatWindow::clear() {
    //qDebug() << "message size: " << messages.size();
    for (quint32 i = 0; i < messages.size(); i++) {
        if (!messages[i]) {
            //qDebug() << "GGGGGGGGGGGGGGGGGGGGGGGGGGGG";
            continue ;
        }
        messages[i]->close();
        delete messages[i];
        //qDebug() << "success " << i;
    }
    messages.clear();
    ui->inputEdit->setPlainText("");
    //ui->MsgEdit->setHtml("");
}

void ChatWindow::slot_r_talk(const QJsonObject &obj) {
    qint64 id = obj.value("chatId").toInt();
    if (id > 0) {
        switchChat(id);
        //Director::getInstance()->raiseChat(id);
    }
}

//switching chat
void ChatWindow::switchChat(qint64 id) {
    //qDebug() << "start switch";
    if (id != chatId) {
        clear();
    }
    if (id == 0) {
        ui->idLabel->setText(tr("尚未打开任何群聊"));
        ui->inputEdit->setReadOnly(true);
        return ;
    }
    ui->inputEdit->setReadOnly(false);
    chatId = id;
    QJsonObject msg;
    msg.insert("type", "q_chatHistory");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("count", 64);
    Director::getInstance()->sendJson(msg);
    //qDebug() << "end switch";
}

void ChatWindow::slot_r_chatHistory(const QJsonObject &obj) {
    if (recvChatId(obj) != chatId) {
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
    //updateText();
    updateMessage();
}

void ChatWindow::slot_a_newMessage(const QJsonObject &obj) {
    qint64 recvId = recvChatId(obj);
    if (recvId != chatId) {
        Director::getInstance()->raiseChat(recvId);
        return ;
    }
    if (!obj.value("message").isObject()) {
        return ;
    }
    QJsonObject msg = obj.value("message").toObject();
    Message cur = jsonToMessage(msg);
    history.append(cur);
    //appendText(messageToString(cur));
    //updateText();
    updateMessage();
}

ChatWindow::Message ChatWindow::jsonToMessage(const QJsonObject &obj) {
    Message cur;
    cur.type = Text;
    auto setIncompleteMessage = [] (Message &cur) -> void {
        cur.isSystem = true;
        cur.content = tr("Incomplete Message.");
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
    QString name = tr("Bot"), time = tr("Just now");
    if (obj.value("senderName").isString()) {
        name = obj.value("senderName").toString();
    }
    if (obj.value("time").isString()) {
        time = obj.value("time").toString();
    }
    else {
        cur.isSystem = true;
    }
    cur.isSystem = false;
    cur.senderId = obj.value("senderId").toInt();
    //cur.senderName = "Carol" + QString::number(cur.senderId);
    cur.senderName = name;
    cur.time = time;
    cur.content = obj.value("content").toString();
    while (cur.content.endsWith('\n') || cur.content.endsWith(' ')) {
        cur.content.removeLast();
    }
    if (cur.content.length() == 0) {
        cur.content = tr("...");
    }
    if (true == obj.value("is_file").toBool()) {
        QString format = obj.value("format").toString();
        if ("file" == format) {
            cur.type = File;
        }
        else if ("photo" == format) {
            cur.type = Picture;
        }
        else if ("audio" == format) {
            cur.type = Voice;
            //qDebug() << "recv voice";
        }
    }
    else {
        cur.type = Text;
    }
    return cur;
}
/*
QString ChatWindow::messageToString(const Message &cur) {
    QString one;
    one.append(cur.senderName);
    if (cur.senderId > 0) {
        one.append(" (" + QString::number(cur.senderId) + ")");
    }
    one.append("\n" + cur.content + "\n");
    return one;
}
*/
// now String is html
// upd: outdated. do not use this.
QString ChatWindow::messageToString(const Message &cur) {
    QString color;
    if (cur.senderId == Director::getInstance()->myId()) {
        // myself
        color = "#4477CE";
    }
    else if (cur.senderId == 0) {
        // bot
        color = "#5C469C";
    }
    else {
        // others
        color = "black";
    }
    QString style="display:flex;flex-directon:column;margin:12px 0px 12px 0px;color:" + color;
    // !keep this strange indentation for HTML
    QString one;
    one.append("<div style=\"" + style + "\">");
        one.append("<table style=\"border:0;border-collapse:collapse;\"><tr>");
            one.append("<td style=\"font-size:16px\">");
                one.append(cur.senderName.toHtmlEscaped());
                if (cur.senderId > 0) {
                    one.append(" (" + QString::number(cur.senderId).toHtmlEscaped() + ")");
                }
            one.append("</td>");
            one.append("<td style=\"vertical-align:middle;font-size:10px;padding-left:8px\">" + tr("发送于 ") + cur.time.toHtmlEscaped() + "</td>");
            //one.append("<div style=\"clear:both\"></div>");
        one.append("</tr></table>");
        one.append("<div style=\"font-size:15px;margin-top:5px\">" + cur.content.toHtmlEscaped() + "</div>");
    one.append("</div>");
    return one;
}

QWidget* ChatWindow::messageToWidget(const Message &cur) {
    const quint32 gap = 0;
    if (Text == cur.type) {
                    QWidget *res = new QWidget(ui->messageArea);
                    const quint32 width = ui->messageArea->width() - 16;
                    /*QString color;
                    if (cur.senderId == Director::getInstance()->myId()) {
                        // myself
                        color = "#4477CE";
                    }
                    else if (cur.senderId == 0) {
                        // bot
                        color = "#5C469C";
                    }
                    else {
                        // others
                        color = "black";
                    }
                    res->setFixedWidth(width);
                    QTextEdit *head = new QTextEdit(res);
                    head->setFixedWidth(width - gap - gap);
                    head->setText(cur.senderName + " (" + QString::number(cur.senderId) + ")");
                    head->setStyleSheet(QString("QTextEdit { border: none; font-size: 16px; color: %1 }").arg(color));
                    head->move(gap, gap);
                    QTextEdit *body = new QTextEdit(res);
                    body->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    body->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
                    body->setFixedWidth(width - gap - gap);
                    body->setText(cur.content);
                    body->setStyleSheet(QString("QTextEdit { border: none; font-size: 15px; color: %1 }").arg(color));
                    body->move(gap, head->height() + gap);
                    body->document()->adjustSize();
                    qint32 docHeight = body->document()->size().height();
                    qDebug() << "docHeight " << docHeight;
                    body->setFixedHeight(docHeight);*/
                    /*QAbstractTextDocumentLayout *layout = body->document()->documentLayout();
                    QSizeF htmlSize = layout->documentSize();
                    qDebug() << htmlSize;
                    body->setFixedHeight(htmlSize.height());*/
                    QTextEdit *text = new QTextEdit(res);
                    text->setFixedWidth(width - gap - gap);
                    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    text->setStyleSheet("QTextEdit { border: none; }");
                    QString one = messageToString(cur);
                    text->setHtml(one);
                    text->document()->adjustSize();
                    qint32 docHeight = text->document()->size().height();
                    //qDebug() << "docHeight " << docHeight;
                    text->setFixedHeight(docHeight);
                    res->adjustSize();
                    res->show();
                    return res;
    }
    else if (Picture == cur.type) {
                    photoMessage *res = new photoMessage(ui->messageArea);
                    res->init(cur, chatId, &waiting);
                    res->show();
                    return res;
    }
    else if (Voice == cur.type) {
                    audioMessage *res = new audioMessage(ui->messageArea);
                    res->init(cur, chatId, &waiting);
                    res->show();
                    return res;
    }
    else if (File == cur.type) {
                    QWidget *res = new QWidget(ui->messageArea);
                    return res;
    }
    //qDebug() << "nullptr!!!!!!!!!!!!!!!!..";
    return nullptr;
}

/*
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
*/
void ChatWindow::updateText() {
    // QVector<Message> history -> lineEdit->text()
    QString all;
    ui->MsgEdit->setHtml("");
    all.append("<div style=\"display:flex;flex-directon:column;margin-left:5px\">");
    for (quint32 i = 0; i < history.size(); i++) {
        QString cur = "<div>";
        cur += messageToString(history[i]);
        cur += "</div>";
        all.append(cur);
        //ui->MsgEdit->insertHtml(cur);
    }
    all.append("</div>");
    all.append("<div style=\"margin:20px 0px 20px 0px\"></div>");
    ui->MsgEdit->setHtml(all);
    QTextCursor cursor = ui->MsgEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->MsgEdit->setTextCursor(cursor);
}

void ChatWindow::updateMessage() {
    //updateText();
    clear();
    quint32 siz = history.size();
    messages.resize(siz);
    const quint32 gap = 5;
    quint32 height = gap;
    for (quint32 i = 0; i < siz; i++) {
        auto *p = messages[i] = messageToWidget(history[i]);
        p->move(gap, height);
        p->show();
        height += /*gap + */p->height();
    }
    ui->messageArea->adjustSize();
    auto *roll = ui->scrollArea->verticalScrollBar();
    roll->setValue(roll->maximum());
}

void ChatWindow::appendText(const QString &text) {
    ui->MsgEdit->insertPlainText(text + "\n");
    // outdated. do not use this.
}

void ChatWindow::on_sendButton_clicked()
{
   if (0 == waiting) {
        if (ui->inputEdit->toPlainText().length() == 0) {
            return ;
        }
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
    if (chatId == 0) {
        show_error();
        return ;
    }
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
        msg.insert("format", QJsonValue("file"));
        if (Director::getInstance()->sendJson(msg)) {
            waiting++;
        }
    }
}

void ChatWindow::slot_r_updateFile(const QJsonObject &obj) {
    if (obj.value("format") != "file"){
        return;
    }
    waiting--;
    if (!obj.value("success").isBool()) {
        return ;
    }
    if (true == obj.value("success").toBool()) {
        return ;
    }
}

void ChatWindow::show_error(){
    QMessageBox box;
    box.setStyleSheet("QLabel{"
            "min-width:100px;"
            "min-height:40px; "
            "font-size:16px;"
            "}");
    box.setText(QString::fromLocal8Bit("请先打开群聊"));
    box.setWindowTitle(QString::fromLocal8Bit("警告"));
    box.setIcon(QMessageBox::Icon::Warning );
    box.addButton(QString::fromLocal8Bit("确定"), QMessageBox::AcceptRole);
    box.exec();
}

void ChatWindow::on_pushButton_clicked()
{
    if (chatId == 0) {
        show_error();
        return ;
    }
    if (nullptr == dl){
        dl = new fileDownload();
        dl->set(&chatId, &waiting, true);
    } else {
        if (true == dl->isVisible())
            dl->close();
        else{
            dl->set(&chatId, &waiting, false);
        }
    }
}

void ChatWindow::on_settingsButton_clicked()
{
    if (chatId == 0) {
        show_error();
        return ;
    }
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

void ChatWindow::on_audioButton_clicked()
{
    if (chatId == 0) {
        show_error();
        return ;
    }
    if (nullptr == ar){
        ar = new audioRecord();
        ar->show();
        ar->set(&chatId, &waiting);
    } else {
        if (true == ar->isVisible())
            ar->close();
        else{
            ar->show();
            ar->set(&chatId, &waiting);
        }
    }
}

void ChatWindow::on_photoButton_clicked()
{
    if (chatId == 0) {
        show_error();
        return ;
    }
    qDebug() << waiting;
    if (0 == waiting) {
        QString str = QFileDialog::getOpenFileName(this, tr("Select photo"), "" , "Image(*.png *.jpg *.bmp)");
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
        msg.insert("format", QJsonValue("photo"));
        if (Director::getInstance()->sendJson(msg)) {
            waiting++;
        }
    }
}

