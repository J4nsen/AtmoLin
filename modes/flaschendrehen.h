#ifndef FLASCHENDREHEN_H
#define FLASCHENDREHEN_H

#include "abstractmode.h"
#include <QTimer>
class Flaschendrehen : public AbstractMode
{
    Q_OBJECT
public:
    explicit Flaschendrehen(QList<LEDArea *> leds, QObject *parent = 0);
private:
    quint32 m_secondsBetweenRoundsMin;
    quint32 m_secondsBetweenRoundsMax;
    QTimer *m_roundTimer;

    QTimer *m_flickrTimeoutTimer;
    QTimer *m_flickrIntervalTimer;
    QTimer *m_dimTimer;

    int m_randLight;

    void startRoundTimer();

signals:

public slots:
private slots:
    void startNewRound();
    void on_flickerIntervalTimerTimeout();
    void on_flickerTimeoutTimerTimeout();
    void on_dimTimerTimeout();
};

#endif // FLASCHENDREHEN_H
