#include "abstractmode.h"

AbstractMode::AbstractMode(QList<LEDArea *> leds, QObject *parent) :
    QObject(parent),
    m_ledAreaListOrdered(leds)
{
    m_widget = new QWidget();
}

AbstractMode::~AbstractMode()
{
    delete m_widget;
}

QWidget *AbstractMode::widget()
{
    return m_widget;
}
