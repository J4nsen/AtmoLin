#include "remotedbus.h"
#include <QDebug>

RemoteDBus::RemoteDBus(QList<LEDArea*> leds,  QObject *parent):
    AbstractMode(leds, parent)
{
    setObjectName("RemoteDBus");
}

RemoteDBus::~RemoteDBus()
{

}

void RemoteDBus::on_updateLEDs()
{
    emit updateLEDs();
}

