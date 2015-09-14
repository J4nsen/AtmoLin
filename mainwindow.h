#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <color_wheel.hpp>
#include "atmolight.h"
#include <QSystemTrayIcon>

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
    void on_colorChanged(QColor color);
    void loadSettings();
    void on_systemTrayActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    QList<AtmoLight*> m_atmoLightList;
    QSystemTrayIcon *m_tray;

    color_widgets::ColorWheel *m_cw;


    void saveSettings();
};

#endif // MAINWINDOW_H

