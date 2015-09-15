#include "individualfixedcolor.h"
#include <QDebug>
#include <QHBoxLayout>


IndividualFixedColor::IndividualFixedColor(QList<LEDArea *> leds, QObject *parent) :
    AbstractMode(leds, parent)
{
    setObjectName("IndividualFixedColor");
    qDebug() << this << "Created";

    m_widget = new QWidget();
    m_widget->setLayout(new QHBoxLayout());

    m_cw = new color_widgets::ColorWheel();
    connect(m_cw, SIGNAL(colorChanged(QColor)), this, SLOT(on_colorChanged(QColor)));
    m_widget->layout()->addWidget(m_cw);

    m_spinBox = new QSpinBox();
    connect(m_spinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBoxValueChanged(int)));
    m_spinBox->setMinimum(0);
    m_spinBox->setMaximum(m_ledAreaListOrdered.size()-1);
    m_widget->layout()->addWidget(m_spinBox);

}

IndividualFixedColor::~IndividualFixedColor()
{
    QSettings s;
    s.beginGroup(objectName());
    for(int i = 0; i < m_ledAreaListOrdered.size(); i++){
        s.setValue(QString::number(i), m_ledAreaListOrdered[i]->color());
    }

    s.setValue("index", m_spinBox->value());
    s.endGroup();
    qDebug() << this << "Quitting";

    delete m_widget;
}

QWidget *IndividualFixedColor::widget()
{
    return m_widget;
}

void IndividualFixedColor::on_colorChanged(QColor color)
{
    m_ledAreaListOrdered[m_spinBox->value()]->setColor(color);
    emit updateLEDs();
}

void IndividualFixedColor::on_spinBoxValueChanged(int val)
{
    m_cw->setColor(m_ledAreaListOrdered[val]->color());
}

void IndividualFixedColor::on_loadSettingsTimeOut()
{
    QSettings s;
    s.beginGroup(objectName());
    QStringList keys = s.childKeys();
    qDebug() << this << keys;
    int i = 0;
    if(keys.size() >= m_ledAreaListOrdered.size()){
        foreach(LEDArea *led, m_ledAreaListOrdered){
            qDebug() << this << "Setting color";
            led->setColor(s.value(keys[i]).value<QColor>());
            i++;
        }

        m_spinBox->setValue(s.value("index", 0).toInt());
        m_cw->setColor(m_ledAreaListOrdered[m_spinBox->value()]->color());

        emit updateLEDs();
    }

}

