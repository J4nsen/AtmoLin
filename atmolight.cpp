#include "atmolight.h"
#include <QDebug>

AtmoLight::AtmoLight(QString portName, QObject *parent) :
    QObject(parent),
    m_serialPortName(portName)
{
    m_serialPort.setPortName(m_serialPortName);
    m_serialPort.setBaudRate(38400);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    for(int i = 0; i<4;i++){
        LEDArea *ledarea = new LEDArea();
        m_ledAreaList.append(ledarea);
    }
}

AtmoLight::~AtmoLight()
{
    m_serialPort.close();
}

void AtmoLight::connectToBoard()
{
    m_serialPort.open(QIODevice::WriteOnly);
}

void AtmoLight::sendLightState()
{
    QByteArray command = QByteArray::fromHex("FF 00 00 0F 00 00 00");
    foreach (LEDArea *led, m_ledAreaList) {
        QByteArray color;
        // R
        color.append((char)led->red());
        // G
        color.append((char)led->green());
        // B
        color.append((char)led->blue());

        command.append(color);
    }

    qDebug() << this << "Sending" << command.toHex();
    m_serialPort.write(command);
}

QList<LEDArea *> AtmoLight::ledAreaList() const
{
    return m_ledAreaList;
}

void AtmoLight::setLedAreaList(const QList<LEDArea *> &ledAreaList)
{
    m_ledAreaList = ledAreaList;
}


