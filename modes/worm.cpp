#include "worm.h"

#include <QHBoxLayout>
Worm::Worm(QList<LEDArea *> leds, QObject *parent) :
    AbstractMode(leds, parent),
    m_interval(50)
{
    m_widget = new QWidget();
    m_widget->setLayout(new QHBoxLayout());


    m_intervalTimer = new QTimer(this);
    connect(m_intervalTimer, SIGNAL(timeout()), this, SLOT(on_timeOut()));
    m_intervalTimer->setInterval(m_interval);
    m_intervalTimer->start();

    //
    m_spinBox = new QSpinBox();
    m_spinBox->setMaximum(60000);
    connect(m_spinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_valueChanged(int)));
    m_spinBox->setSuffix("ms");
    m_spinBox->setValue(m_interval);
    m_widget->layout()->addWidget(m_spinBox);
    //

}

Worm::~Worm()
{
    delete m_spinBox;
    delete m_widget;
}

QWidget *Worm::widget()
{
    return m_widget;
}

void Worm::on_timeOut()
{
    QList<QColor> colorList;

    int size = m_ledAreaListOrdered.size();
    QColor tmpColor = m_ledAreaListOrdered[0]->color();
    for(int i = 0; i < size; i++) {
        m_ledAreaListOrdered[i]->setColor( m_ledAreaListOrdered[(i+1)%size]->color() );
    }
    m_ledAreaListOrdered[size-1]->setColor(tmpColor);

    emit updateLEDs();
}

void Worm::on_spinBox_valueChanged(int val)
{
    m_interval = val;
    m_intervalTimer->setInterval(m_interval);
}
