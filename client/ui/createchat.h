#ifndef CREATECHAT_H
#define CREATECHAT_H

#include <QDialog>
#include <QButtonGroup>
#include <QJsonObject>
#include <QSet>

namespace Ui {
class CreateChat;
}

class CreateChat : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChat(QWidget *parent = nullptr);
    ~CreateChat();
    void clear();
    void addChoice(quint32, const QString&);
    void update();

public slots:
    void slot_r_createChat(const QJsonObject&);

private slots:
    void checkStateChanged(qint32 id, bool state);

    void on_pushButton_clicked();

private:
    Ui::CreateChat *ui;
    QButtonGroup *choices;
    QSet<qint64> chosen;
};

#endif // CREATECHAT_H
