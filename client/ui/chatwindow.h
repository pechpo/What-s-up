#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QVector>
#include <QJsonObject>

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
    void on_r_chatHistory(const QJsonObject&);
    void on_a_newMessage(const QJsonObject&);

private:
    Ui::ChatWindow *ui;

    bool isThisChat(const QJsonObject&);

    qint64 chatId;
    class Message {
        qint64 senderId;
        QString senderName;
        QString content;
    };
    QVector<Message> history;
    void updateText();
};

#endif // CHATWINDOW_H
