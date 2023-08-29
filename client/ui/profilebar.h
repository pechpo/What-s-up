#ifndef PROFILEBAR_H
#define PROFILEBAR_H

#include <QWidget>

namespace Ui {
class ProfileBar;
}

class ProfileBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileBar(QWidget *parent = nullptr);
    ~ProfileBar();
    void setName(const QString&);
    void setAvatar(const QString&);
    QString getName();

private:
    Ui::ProfileBar *ui;
    QString avatar;
};

#endif // PROFILEBAR_H
