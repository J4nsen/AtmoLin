#include "ledarea.h"
#include <QDebug>

LEDArea::LEDArea(int id, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_color(0,0,0)
{
    this->setObjectName(QString::number(m_id));
}

LEDArea::~LEDArea()
{
    qDebug() << this << "Quitting";
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

