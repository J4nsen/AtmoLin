#ifndef ATMOLIGHT_H
#define ATMOLIGHT_H

#include <QObject>
#include <QSerialPort>

#include "ledarea.h"

class AtmoLight : public QObject
{
    Q_OBJECT
public:
    explicit AtmoLight(QObject *parent = 0);
    ~AtmoLight();
    void connectToBoard();
    void sendLightState();

    QString serialPortName() const;
    void setSerialPortName(const QString &serialPortName);

    QList<LEDArea *> ledAreaList() const;
    void setLedAreaList(const QList<LEDArea *> &ledAreaList);

private:
    QSerialPort m_serialPort;
    QString m_serialPortName;
    QList<LEDArea*> m_ledAreaList;
signals:

public slots:

};

#endif // ATMOLIGHT_H
