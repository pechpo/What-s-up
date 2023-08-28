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

private:
    Ui::ProfileBar *ui;
};

#endif // PROFILEBAR_H
