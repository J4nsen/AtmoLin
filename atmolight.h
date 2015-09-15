#ifndef ATMOLIGHT_H
#define ATMOLIGHT_H

#include <QObject>
#include <QSerialPort>

#include "ledarea.h"

class AtmoLight : public QObject
{
    Q_OBJECT
public:
    explicit AtmoLight(QString portName, QList<int> order, QObject *parent = 0);
    ~AtmoLight();
    void connectToBoard();
    void sendLightState();


    QList<LEDArea *> ledAreaList() const;
    void setLedAreaList(const QList<LEDArea *> &ledAreaList);

    QList<int> ledAreaOrderList() const;
    void setLedAreaOrderList(const QList<int> &ledAreaOrderList);

private:
    QSerialPort m_serialPort;
    QString m_serialPortName;
    QList<LEDArea*> m_ledAreaList;
    QList<int> m_ledAreaOrderList;
signals:

public slots:

};

#endif // ATMOLIGHT_H
