#include "flaschendrehen.h"

#include <QDebug>
#include <QRandomGenerator>

Flaschendrehen::Flaschendrehen(QList<LEDArea *> leds, QObject *parent) :
    AbstractMode(leds, parent),
    m_secondsBetweenRoundsMin(1),
    m_secondsBetweenRoundsMax(2)
{
    //
    m_roundTimer = new QTimer(this);
    connect(m_roundTimer, SIGNAL(timeout()), this, SLOT(startNewRound()));
    //

    //
    m_flickrTimeoutTimer = new QTimer(this);
    connect(m_flickrTimeoutTimer, SIGNAL(timeout()), this, SLOT(on_flickerTimeoutTimerTimeout()));
    m_flickrTimeoutTimer->setInterval(5000);
    //

    //
    m_flickrIntervalTimer = new QTimer(this);
    connect(m_flickrIntervalTimer, SIGNAL(timeout()), this, SLOT(on_flickerIntervalTimerTimeout()));
    m_flickrIntervalTimer->setInterval(50);
    //

    //
    m_dimTimer = new QTimer(this);
    connect(m_dimTimer, SIGNAL(timeout()), this, SLOT(on_dimTimerTimeout()));
    m_dimTimer->setInterval(30);
    //

    startRoundTimer();
}

void Flaschendrehen::startRoundTimer()
{
    // Rand Time
    int diff = m_secondsBetweenRoundsMax-m_secondsBetweenRoundsMin;
    int rand = 0;
    if(diff != 0) rand = ( QRandomGenerator::global()->generate() % diff);
    rand += m_secondsBetweenRoundsMin;
    //
    qDebug() << this << "Next round in" << rand;
    m_roundTimer->start(rand*1000);
}

void Flaschendrehen::startNewRound()
{
    qDebug() << this << "Starting round";
    m_roundTimer->stop();

    // Select Random Light
    m_randLight = QRandomGenerator::global()->generate() % m_ledAreaListOrdered.size();
    qDebug() << this << "Rand light" << m_randLight;
    //

    m_flickrIntervalTimer->start();
    m_flickrTimeoutTimer->start();
}

void Flaschendrehen::on_flickerIntervalTimerTimeout()
{
    // Generate random Colors
    QList<QColor> randColorList;
    for(int i=0; i<m_ledAreaListOrdered.size(); i++){
        QColor randColor;
        randColor.setHsv(QRandomGenerator::global()->generate()%360, 255, 255);
        randColorList.append(randColor);
    }

    int i = 0;
    foreach(LEDArea *led, m_ledAreaListOrdered){
        led->setColor(randColorList[i]);
        i++;
    }

    emit updateLEDs();
}

void Flaschendrehen::on_flickerTimeoutTimerTimeout()
{
    m_flickrIntervalTimer->stop();
    m_dimTimer->start();
}

void Flaschendrehen::on_dimTimerTimeout()
{
    int i = 0;
    foreach(LEDArea *led, m_ledAreaListOrdered){
        if(i != m_randLight) led->setColor(led->color().darker(110));
        i++;
    }
    emit updateLEDs();
}
