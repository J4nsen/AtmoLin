#ifndef ONEFIXEDCOLOR_H
#define ONEFIXEDCOLOR_H

#include "abstractmode.h"
#include <QtColorWidgets/color_wheel.hpp>
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
    void on_loadSettingsTimeOut();

};

#endif // ONEFIXEDCOLOR_H
