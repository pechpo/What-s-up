#include "createchat.h"
#include "ui_createchat.h"
#include "director/director.h"
#include <QList>
#include <QJsonValue>
#include <QJsonArray>
#include <QCheckBox>

CreateChat::CreateChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);

    choices = new QButtonGroup(ui->scrollAreaWidgetContents);
    choices->setExclusive(false);
    QString style = R"(
        QPushButton {
            border: none;
            background-color: rgba(59, 180, 193,0.75);
            border-radius:10px;
        }
        QPushButton:hover {
            background-color: rgba(59, 180, 193, 1);
        }
    )";
    ui->pushButton->setStyleSheet(style);
    chosen.clear();
    connect(choices, &QButtonGroup::idToggled, this, &CreateChat::checkStateChanged);
    connect(Director::getInstance(), &Director::r_createChat, this, &CreateChat::slot_r_createChat);
}

CreateChat::~CreateChat()
{
    delete ui;
}

void CreateChat::clear() {
    auto lis = choices->buttons();
    for (quint32 i = 0; i < lis.size(); i++) {
        choices->removeButton(lis[i]);
    }
}

void CreateChat::addChoice(quint32 id, const QString &name) {
    QCheckBox *box = new QCheckBox(name, ui->scrollAreaWidgetContents);
    choices->addButton(box, id);
}

void CreateChat::update() {
    const quint32 gap = 5;
    quint32 height = gap;
    auto lis = choices->buttons();
    for (quint32 i = 0; i < lis.size(); i++) {
        auto p = lis[i];
        p->move(gap, height);
        height += p->height() + gap;
    }
}

void CreateChat::checkStateChanged(qint32 id, bool state) {
    if (true == state && !chosen.contains(id)) {
        chosen.insert(id);
    }
    else if (false == state && chosen.contains(id)) {
        chosen.remove(id);
    }
}

void CreateChat::on_pushButton_clicked()
{
    QJsonObject msg;
    QJsonArray arr;
    for (auto &i : chosen) {
        qint64 val = i;
        arr.push_back(QJsonValue(val));
    }
    msg.insert("type", "e_createChat");
    msg.insert("users", arr);
    Director::getInstance()->sendJson(msg);
}

void CreateChat::slot_r_createChat(const QJsonObject &obj) {
    if (true == obj.value("success").toBool()) {
        accept();

    }
}

