#ifndef INDIVIDUALFIXEDCOLOR_H
#define INDIVIDUALFIXEDCOLOR_H

#include "abstractmode.h"
#include <QtColorWidgets/color_wheel.hpp>
#include <QSpinBox>
#include <QVBoxLayout>

class IndividualFixedColor : public AbstractMode
{
    Q_OBJECT
public:
    explicit IndividualFixedColor(QList<LEDArea *> leds, QObject *parent = 0);
    ~IndividualFixedColor();
    QWidget* widget();
private:
    color_widgets::ColorWheel *m_cw;
    QWidget *m_widget;
    QVBoxLayout *m_layout;
    QSpinBox *m_spinBox;
signals:

public slots:
private slots:
    void on_colorChanged(QColor color);
    void on_spinBoxValueChanged(int val);
    void on_loadSettingsTimeOut();


};

#endif // INDIVIDUALFIXEDCOLOR_H
