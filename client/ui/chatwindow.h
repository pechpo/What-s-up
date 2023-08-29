#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QVector>
#include <QJsonObject>
#include "filedownload.h"
#include "chatsettings.h"

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

private:
    Ui::ChatWindow *ui;
    fileDownload *dl;
    ChatSettings *settingsDialog;

    quint32 waiting;

    bool isThisChat(const QJsonObject&);

    qint64 chatId;
    struct Message {
        bool isSystem;
        qint64 senderId;
        QString senderName;
        QString content;
    };
    QVector<Message> history;
    Message jsonToMessage(const QJsonObject&);
    QString messageToString(const Message&);
    void updateText();
};

#endif // CHATWINDOW_H
