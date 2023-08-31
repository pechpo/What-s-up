#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QDialog>
#include <QButtonGroup>
#include <QJsonObject>

namespace Ui {
class TagEditor;
}

class TagEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TagEditor(QWidget *parent = nullptr);
    ~TagEditor();


public slots:
    void slot_r_list_tags(const QJsonObject&);
    void slot_r_editTags(const QJsonObject&);
    void slot_r_list_recommend(const QJsonObject&);

private slots:
    void checkStateChanged(qint32 id, bool state);
    void on_confirmButton_clicked();

private:
    Ui::TagEditor *ui;
    QButtonGroup *choices;
    QVector<QPair<QString, bool> > state;
};

#endif // TAGEDITOR_H
