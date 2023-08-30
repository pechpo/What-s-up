#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include "filedownload.h"
#include "audiorecord.h"
#include "chatsettings.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

    void switchChat(qint64);
    void appendText(const QString&);
    void show_error();

public slots:
    void slot_r_chatHistory(const QJsonObject&);
    void slot_a_newMessage(const QJsonObject&);
    void slot_r_send(const QJsonObject&);
    void slot_r_updateFile(const QJsonObject &obj);

private slots:
    void on_sendButton_clicked();

    void on_fileButton_clicked();

    void on_pushButton_clicked();

    void on_settingsButton_clicked();

    void on_audioButton_clicked();

    void on_photoButton_clicked();

private:
    Ui::ChatWindow *ui;
    fileDownload *dl;
    audioRecord *ar;
    ChatSettings *settingsDialog;

    quint32 waiting;

    qint64 recvChatId(const QJsonObject&);

    qint64 chatId;
    enum MsgType {
        Text, File, Picture, Voice
    };
    struct Message {
        bool isSystem;
        MsgType type;
        qint64 senderId;
        QString time;
        QString senderName;
        QString content;
    };
    QVector<Message> history;
    QVector<QWidget*> messages;
    void clear();
    Message jsonToMessage(const QJsonObject&);
    QString messageToString(const Message&);
    QWidget* messageToWidget(const Message&);
    void updateMessage();
    void updateText(); // outdated. do not use this
};

#endif // CHATWINDOW_H
