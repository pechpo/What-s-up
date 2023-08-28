#include "customtoolbutton.h"

CustomToolButton::CustomToolButton(QWidget *parent)
    : QToolButton(parent) {}

void CustomToolButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStylePainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);

    // Clear the arrow (menu indicator) from the option
    opt.features &= ~QStyleOptionToolButton::HasMenu;

    p.drawComplexControl(QStyle::CC_ToolButton, opt);
}
