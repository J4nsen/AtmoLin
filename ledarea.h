#ifndef LEDAREA_H
#define LEDAREA_H

#include <QObject>
#include <QColor>

class LEDArea : public QObject
{
    Q_OBJECT
public:
    explicit LEDArea(int id, QObject *parent = 0);
    ~LEDArea();

    QColor color() const;
    void setColor(const QColor &color);

    int red();
    int green();
    int blue();

private:
    int m_id;
    QColor m_color;
signals:

public slots:

};

#endif // LEDAREA_H

