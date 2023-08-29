#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include <QWidget>

namespace Ui {
class fileDownload;
}

class fileDownload : public QWidget
{
    Q_OBJECT

public:
    explicit fileDownload(QWidget *parent = nullptr);
    void set(qint64 chatId, quint32 &waiting);
    ~fileDownload();

public slots:
    void slot_r_list_filesInChat(const QJsonObject &obj);

private:
    Ui::fileDownload *ui;

};

#endif // FILEDOWNLOAD_H
