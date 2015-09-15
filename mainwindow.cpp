#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ledarea.h"

#include <QSettings>
#include <QDebug>
#include <QTimer>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // App name
    QApplication::setOrganizationName("Jan Wiele");
    QApplication::setOrganizationDomain("wiele.org");
    QApplication::setApplicationName("AtmoLin");
    //

    // Colorwheel
    m_cw = new color_widgets::ColorWheel(this);
    ui->gridLayout->addWidget(m_cw);
    connect(m_cw, SIGNAL(colorChanged(QColor)), this, SLOT(on_colorChanged(QColor)));
    //

    // Atmolights
    AtmoLight *al;

    al = new AtmoLight("/dev/atmolight-right", this);
    m_atmoLightList.append(al);

    al = new AtmoLight("/dev/atmolight-left", this);
    m_atmoLightList.append(al);
    //

    // Systray
    m_tray = new QSystemTrayIcon(this);
    connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(on_systemTrayActivated(QSystemTrayIcon::ActivationReason)));
    m_tray->setContextMenu(ui->menuBar->findChildren<QMenu*>().first());
    m_tray->setIcon(QIcon(":/img/icon"));
    m_tray->show();
    //

    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::loadSettings()
{
    qDebug() << this << "Loading Settings";
    QSettings s;
    m_cw->setColor(s.value("color").value<QColor>());
}

void MainWindow::on_systemTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << this << "SystemTray activated. Reason:" << reason;
    switch(reason){
    case QSystemTrayIcon::Unknown:{

    }
    case QSystemTrayIcon::Context:{

    }
    case QSystemTrayIcon::DoubleClick:{

    }
    case QSystemTrayIcon::Trigger:{
        this->show();
    }
    case QSystemTrayIcon::MiddleClick:{

    }
    default:{

    }
    }
}

void MainWindow::saveSettings()
{
    qDebug() << this << "Saving Settings";
    QSettings s;
    s.setValue("color", m_cw->color());
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::instance()->quit();
}

void MainWindow::on_colorChanged(QColor color)
{
    foreach(AtmoLight *al, m_atmoLightList){
        foreach(LEDArea *led, al->ledAreaList()){
            led->setColor(color);
        }
    }
    foreach(AtmoLight *al, m_atmoLightList){
        al->sendLightState();
    }
}

