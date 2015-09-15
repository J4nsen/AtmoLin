#include "onefixedcolor.h"

#include <QDebug>

OneFixedColor::OneFixedColor(QList<LEDArea*> leds, QObject *parent) :
    AbstractMode(leds, parent)
{
    setObjectName("OneFixedColor");
    qDebug() << this << "Created";
    m_cw = new color_widgets::ColorWheel();
    connect(m_cw, SIGNAL(colorChanged(QColor)), this, SLOT(on_colorChanged(QColor)));
    QSettings s;
    m_cw->setColor(s.value(objectName()).value<QColor>());
}

OneFixedColor::~OneFixedColor()
{
    QSettings s;
    s.setValue(objectName(), m_cw->color());
    qDebug() << this << "Quitting";
    delete m_cw;
}

QWidget *OneFixedColor::widget()
{
    return m_cw;
}

void OneFixedColor::on_colorChanged(QColor color)
{
    foreach (LEDArea *led, m_ledAreaListOrdered) {
        led->setColor(color);
    }
    emit updateLEDs();
}
