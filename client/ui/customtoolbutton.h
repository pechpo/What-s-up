#pragma once

#include <QToolButton>
#include <QStylePainter>
#include <QStyleOptionToolButton>

class CustomToolButton : public QToolButton {
    Q_OBJECT
public:
    explicit CustomToolButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};
