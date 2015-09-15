#ifndef WORM_H
#define WORM_H

#include "abstractmode.h"
#include <QTimer>

class Worm : public AbstractMode
{
    Q_OBJECT
public:
    explicit Worm(QList<LEDArea *> leds, QObject *parent = 0);
    ~Worm();
private:
    QTimer *m_intervalTimer;
signals:

public slots:
private slots:
    void on_timeOut();
};

#endif // WORM_H
