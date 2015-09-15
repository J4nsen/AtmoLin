#include "abstractmode.h"

AbstractMode::AbstractMode(QList<LEDArea *> leds, QObject *parent) :
    QObject(parent),
    m_ledAreaListOrdered(leds)
{
    m_widget = new QWidget();
    QTimer::singleShot(0, this, SLOT(on_loadSettingsTimeOut()));
}

AbstractMode::~AbstractMode()
{
    delete m_widget;
}

QWidget *AbstractMode::widget()
{
    return m_widget;
}

void AbstractMode::on_loadSettingsTimeOut()
{

}
