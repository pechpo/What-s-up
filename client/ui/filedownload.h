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
    void set(qint64 chatId, quint32 *waiting, bool init);
    ~fileDownload();

public slots:
    void slot_r_list_filesInChat(const QJsonObject &obj);
    void slot_r_downloadFile(const QJsonObject &obj);

private slots:
    void on_Download_clicked();

private:
    Ui::fileDownload *ui;
    qint64 chatId;
    quint32 *waiting;
};

#endif // FILEDOWNLOAD_H
