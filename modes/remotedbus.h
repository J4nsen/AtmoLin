#ifndef REMOTEDBUS_H
#define REMOTEDBUS_H

#include "abstractmode.h"

class RemoteDBus : public AbstractMode
{
    Q_OBJECT
public:
    RemoteDBus(QList<LEDArea *> leds, QObject *parent = 0);
    ~RemoteDBus();

signals:

public slots:
    void on_updateLEDs();
};

#endif // REMOTEDBUS_H
