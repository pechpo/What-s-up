#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "profilebar.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

public slots:
    void slot_r_myInfo(const QJsonObject&);
    void slot_r_editInfo(const QJsonObject&);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    ProfileBar *bar;
};

#endif // SETTINGS_H
