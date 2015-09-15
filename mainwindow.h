#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "atmolight.h"
#include <QSystemTrayIcon>
#include "ledarea.h"
#include "modes/abstractmode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void loadSettings();
    void on_systemTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void on_updateLEDs();
    void on_aboutToQuit();
    void on_modeChanged(QString mode);

private:
    Ui::MainWindow *ui;
    QList<AtmoLight*> m_atmoLightList;
    QList<LEDArea*> m_ledAreaListOrdered;

    QSystemTrayIcon *m_tray;
    QColor m_oldColor;

    AbstractMode *m_mode;


    void saveSettings();
};

#endif // MAINWINDOW_H

