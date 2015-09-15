#ifndef INDIVIDUALFIXEDCOLOR_H
#define INDIVIDUALFIXEDCOLOR_H

#include "abstractmode.h"
#include <color_wheel.hpp>
#include <QSpinBox>

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
    QSpinBox *m_spinBox;
signals:

public slots:
private slots:
    void on_colorChanged(QColor color);

};

#endif // INDIVIDUALFIXEDCOLOR_H
