#include "tageditor.h"
#include "ui_tageditor.h"
#include "friendrequest.h"
#include "director/director.h"
#include <QJsonArray>
#include <QCheckBox>

TagEditor::TagEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagEditor)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(false);

    QString confirmstyle = R"(
        QPushButton {
            border: none;
            background-color: rgba(255, 255, 255, 0.75);
            border-radius:10px;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 0.2);
        }
    )";
    ui->confirmButton->setStyleSheet(confirmstyle);

    choices = new QButtonGroup(ui->ScrollContent);
    choices->setExclusive(false);
    state.clear();
    connect(choices, &QButtonGroup::idToggled, this, &TagEditor::checkStateChanged);
    connect(Director::getInstance(), &Director::r_list_tags, this, &TagEditor::slot_r_list_tags);
    connect(Director::getInstance(), &Director::r_editTags, this, &TagEditor::slot_r_editTags);
    connect(Director::getInstance(), &Director::r_list_recommend, this, &TagEditor::slot_r_list_recommend);

    QJsonObject msg;
    msg.insert("type", "q_list_tags");
    Director::getInstance()->sendJson(msg);
}

TagEditor::~TagEditor()
{
    delete ui;
}

void TagEditor::on_confirmButton_clicked()
{
    QJsonArray arr;
    for (quint32 i = 0; i < state.size(); i++) {
        QJsonObject obj;
        obj.insert("tag", state[i].first);
        obj.insert("value", QJsonValue(state[i].second));
        arr.push_back(obj);
    }
    QJsonObject msg;
    msg.insert("editList", arr);
    msg.insert("type", "e_editTags");
    Director::getInstance()->sendJson(msg);
}

void TagEditor::checkStateChanged(qint32 id, bool check) {
    state[id].second = check;
}

void TagEditor::slot_r_list_tags(const QJsonObject &obj) {
    state.clear();
    QJsonArray arr = obj.value("tags").toArray();
    int siz = arr.size();
    state.resize(siz);
    for (quint32 i = 0; i < siz; i++) {
        QJsonObject obj = arr[i].toObject();
        state[i] = qMakePair(obj.value("tag").toString(), obj.value("value").toBool());
        QCheckBox *box = new QCheckBox(state[i].first, ui->ScrollContent);
        if (true == state[i].second) {
            box->setCheckState(Qt::Checked);
        }
        choices->addButton(box, i);
    }
    qDebug() << "show tags";
    const quint32 gap = 5;
    quint32 height = gap;
    auto lis = choices->buttons();
    for (quint32 i = 0; i < lis.size(); i++) {
        auto p = lis[i];
        p->move(gap, height);
        p->show();
        height += p->height() + gap;
    }
    ui->ScrollContent->adjustSize();
}

void TagEditor::slot_r_editTags(const QJsonObject &obj) {
    if (true == obj.value("success").toBool()) {
        auto lis = choices->buttons();
        for (quint32 i = 0; i < lis.size(); i++) {
            auto *p = lis[i];
            p->close();
            choices->removeButton(p);
            delete p;
        }
        ui->confirmButton->setVisible(false);
        setWindowTitle(tr("为你推荐"));
        QJsonObject msg;
        msg.insert("type", "q_list_recommend");
        Director::getInstance()->sendJson(msg);
    }
    else {
        accept();
        close();
    }
}

void TagEditor::slot_r_list_recommend(const QJsonObject &obj) {
    const quint32 gap = 5;
    quint32 height = gap;
    QJsonArray users = obj.value("users").toArray();
    quint32 siz = users.size();
    for (quint32 i = 0; i < siz; i++) {
        if (!users[i].isObject()) {
            continue ;
        }
        QJsonObject user = users[i].toObject();
        auto *p = new FriendRequest(ui->ScrollContent);
        qint64 id = user.value("id").toInt();
        p->setId(id);
        p->setName(user.value("name").toString());
        p->setAvatar(user.value("avatar").toString());
        p->move(gap, height);
        height += p->height() + gap;
        p->show();
    }
    ui->ScrollContent->adjustSize();
}
