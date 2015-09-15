#ifndef ABSTRACTMODE_H
#define ABSTRACTMODE_H

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QSettings>
#include <QTimer>

#include "ledarea.h"

class AbstractMode : public QObject
{
    Q_OBJECT
public:
    explicit AbstractMode(QList<LEDArea*> leds, QObject *parent = 0);
    ~AbstractMode();
    virtual QWidget* widget();
private:
    QWidget *m_widget;

protected:
    QList<LEDArea*> m_ledAreaListOrdered;

signals:
    void updateLEDs();
public slots:

private slots:
    virtual void on_loadSettingsTimeOut();
};

#endif // ABSTRACTMODE_H
