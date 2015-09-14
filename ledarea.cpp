#include "ledarea.h"

LEDArea::LEDArea(QObject *parent) :
    QObject(parent),
    m_color(255,145,0)
{
}

QColor LEDArea::color() const
{    return m_color;
}

void LEDArea::setColor(const QColor &color)
{
    m_color = color;
}

int LEDArea::red()
{
    return m_color.red();
}

int LEDArea::green()
{
    return m_color.green();
}

int LEDArea::blue()
{
    return m_color.blue();
}

