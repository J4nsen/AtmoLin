#include "individualfixedcolor.h"
#include <QDebug>
#include <QHBoxLayout>


IndividualFixedColor::IndividualFixedColor(QList<LEDArea *> leds, QObject *parent) :
    AbstractMode(leds, parent)
{
    setObjectName("IndividualFixedColor");
    qDebug() << this << "Created";

    m_widget = new QWidget();
    m_widget->setLayout(new QHBoxLayout());

    m_cw = new color_widgets::ColorWheel();
    connect(m_cw, SIGNAL(colorChanged(QColor)), this, SLOT(on_colorChanged(QColor)));
    m_widget->layout()->addWidget(m_cw);

    m_spinBox = new QSpinBox();
    m_spinBox->setMinimum(0);
    m_spinBox->setMaximum(m_ledAreaListOrdered.size()-1);
    m_widget->layout()->addWidget(m_spinBox);

}

IndividualFixedColor::~IndividualFixedColor()
{
    delete m_widget;
    qDebug() << this << "Quitting";
}

QWidget *IndividualFixedColor::widget()
{
    return m_widget;
}

void IndividualFixedColor::on_colorChanged(QColor color)
{
    m_ledAreaListOrdered[m_spinBox->value()]->setColor(color);
    emit updateLEDs();
}

