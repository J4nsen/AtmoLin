#include "worm.h"

Worm::Worm(QList<LEDArea *> leds, QObject *parent) :
    AbstractMode(leds, parent)
{
    m_intervalTimer = new QTimer(this);
    connect(m_intervalTimer, SIGNAL(timeout()), this, SLOT(on_timeOut()));

    m_intervalTimer->start(100);
}

Worm::~Worm()
{

}

void Worm::on_timeOut()
{
    QList<QColor> colorList;

    int size = m_ledAreaListOrdered.size();

    for(int i = 0; i < size; i++) {
        m_ledAreaListOrdered[i]->setColor( m_ledAreaListOrdered[(i+1)%size]->color() );
    }

    emit updateLEDs();
}
