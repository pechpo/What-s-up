#include "chatsettings.h"
#include "ui_chatsettings.h"
#include "director/director.h"
#include <QJsonArray>

ChatSettings::ChatSettings(QWidget *parent, qint64 id) :
    QDialog(parent),
    chatId(id),
    ui(new Ui::ChatSettings)
{
    ui->setupUi(this);
    ui->idLabel->setText(QString::number(chatId) + "号聊天");
    ui->scrollArea->setWidgetResizable(false);
    QString exitstyle = R"(
        QPushButton {
            border: none;
            background-color: rgba(176, 71, 89, 0.75);
            border-radius:10px;
        }
        QPushButton:hover {
            background-color: rgba(176, 71, 89, 1);
        }
    )";
    QString changestyle = R"(
        QPushButton {
            border: none;
            background-color: rgba(255, 255, 255, 0.75);
            border-radius:10px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 0.2);
        }
    )";
    ui->exitButton->setStyleSheet(exitstyle);
    ui->confirmButton->setStyleSheet(changestyle);
    connect(Director::getInstance(), &Director::r_chatInfo, this, &ChatSettings::slot_r_chatInfo);
    connect(Director::getInstance(), &Director::r_editChatInfo, this, &ChatSettings::slot_r_editChatInfo);
    connect(Director::getInstance(), &Director::r_exitChat, this, &ChatSettings::slot_r_exitChat);
}

ChatSettings::~ChatSettings()
{
    clear();
    delete ui;
}

void ChatSettings::clear() {
    for (quint32 i = 0; i < userList.size(); i++) {
        userList[i]->close();
        delete userList[i];
    }
    userList.clear();
}

void ChatSettings::on_confirmButton_clicked()
{
    QJsonObject msg;
    msg.insert("type", "e_editChatInfo");
    msg.insert("chatId", QJsonValue(chatId));
    msg.insert("name", ui->chatName->text());
    msg.insert("avatar", ui->chatAvatar->text());
    Director::getInstance()->sendJson(msg);
}

void ChatSettings::slot_r_chatInfo(const QJsonObject &obj) {
    ui->chatName->setText(obj.value("name").toString());
    ui->chatAvatar->setText(obj.value("avatar").toString());
    if (!obj.value("users").isArray()) {
        return ;
    }
    const quint32 gap = 5;
    quint32 height = gap;
    QJsonArray users = obj.value("users").toArray();
    clear();
    quint32 siz = users.size();
    userList.resize(siz);
    for (quint32 i = 0; i < siz; i++) {
        if (!users[i].isObject()) {
            continue ;
        }
        QJsonObject user = users[i].toObject();
        auto *p = userList[i] = new FriendRequest(ui->scrollContent);
        //p->setMinimumWidth(250);
        qint64 id = user.value("id").toInt();
        p->setId(id);
        p->setName(user.value("name").toString());
        p->setAvatar(user.value("avatar").toString());
        p->move(gap, height);
        height += p->height() + gap;
        p->show();
    }
    ui->scrollContent->adjustSize();
    //qDebug() << "successful recv";
}

void ChatSettings::slot_r_editChatInfo(const QJsonObject &obj) {
    if (true == obj.value("success").toBool()) {
        QJsonObject msg;
        msg.insert("type", "q_chatInfo");
        msg.insert("chatId", QJsonValue(chatId));
        Director::getInstance()->sendJson(msg);
        Director::getInstance()->refreshMainWindow(Director::Chat);
    }
}

void ChatSettings::on_exitButton_clicked()
{
    QJsonObject msg;
    msg.insert("type", "e_exitChat");
    msg.insert("chatId", QJsonValue(chatId));
    Director::getInstance()->sendJson(msg);
}

void ChatSettings::slot_r_exitChat(const QJsonObject &obj) {
    if (true == obj.value("success").toBool()) {
        /*QJsonObject msg;
        msg.insert("type", "q_list_myChats");
        Director::getInstance()->sendJson(msg);*/
        Director::getInstance()->refreshMainWindow(Director::Chat);
        Director::getInstance()->enterChat(0);
        accept();
        close();
    }
}
