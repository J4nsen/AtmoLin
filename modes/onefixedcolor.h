#ifndef ONEFIXEDCOLOR_H
#define ONEFIXEDCOLOR_H

#include "abstractmode.h"
#include <color_wheel.hpp>
class OneFixedColor : public AbstractMode
{
    Q_OBJECT
public:
    explicit OneFixedColor(QList<LEDArea *> leds, QObject *parent = 0);
    ~OneFixedColor();
    QWidget* widget();
private:
    color_widgets::ColorWheel *m_cw;
signals:

public slots:
private slots:
    void on_colorChanged(QColor color);

};

#endif // ONEFIXEDCOLOR_H
