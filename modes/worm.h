#ifndef WORM_H
#define WORM_H

#include "abstractmode.h"
#include <QTimer>
#include <QSpinBox>

class Worm : public AbstractMode
{
    Q_OBJECT
public:
    explicit Worm(QList<LEDArea *> leds, QObject *parent = 0);
    ~Worm();

    QWidget* widget();
private:
    QTimer *m_intervalTimer;
    QWidget *m_widget;
    QSpinBox *m_spinBox;
    int m_interval;
signals:

public slots:
private slots:
    void on_timeOut();
    void on_spinBox_valueChanged(int val);
};

#endif // WORM_H
