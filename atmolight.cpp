#include "atmolight.h"
#include <QDebug>

AtmoLight::AtmoLight(QString portName, QList<int> order, QObject *parent) :
    QObject(parent),
    m_serialPortName(portName),
    m_ledAreaOrderList(order)
{
    this->setObjectName(m_serialPortName);

    m_serialPort.setPortName(m_serialPortName);
    m_serialPort.setBaudRate(38400);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    for(int i = 0; i<4;i++){
        LEDArea *ledarea = new LEDArea(i, this);
        m_ledAreaList.append(ledarea);
    }


    connectToBoard();
}

AtmoLight::~AtmoLight()
{
    qDebug() << this << "Quitting";
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

    //qDebug() << this << "Sending" << command.toHex();
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
QList<int> AtmoLight::ledAreaOrderList() const
{
    return m_ledAreaOrderList;
}

void AtmoLight::setLedAreaOrderList(const QList<int> &ledAreaOrderList)
{
    m_ledAreaOrderList = ledAreaOrderList;
}



