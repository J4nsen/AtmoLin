#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QIcon>
#include <QList>

#include "modes/onefixedcolor.h"
#include "modes/individualfixedcolor.h"
#include "modes/worm.h"
#include "modes/flaschendrehen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mode(0)
{
    ui->setupUi(this);

    connect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(on_aboutToQuit()));
    // App name
    QApplication::setOrganizationName("Jan Wiele");
    QApplication::setOrganizationDomain("wiele.org");
    QApplication::setApplicationName("AtmoLin");
    //

    // Atmolights
    //m_atmoLightList.append(new AtmoLight("/dev/atmolight-right", QList<int>() << 1 << 3 << 2 << 0, this));
    //m_atmoLightList.append(new AtmoLight("/dev/atmolight-left", QList<int>() << 3 << 2 << 0 << 1, this));
    m_atmoLightList.append(new AtmoLight("/dev/pts/10", QList<int>() << 1 << 3 << 2 << 0, this));
    m_atmoLightList.append(new AtmoLight("/dev/pts/7", QList<int>() << 3 << 2 << 0 << 1, this));
    //

    // Create ordered list
    foreach(AtmoLight *al, m_atmoLightList){
        for(int i = 0; i<al->ledAreaList().size(); i++){
            m_ledAreaListOrdered.append(al->ledAreaList().at(al->ledAreaOrderList()[i]));
        }
    }
    qDebug() << this << "Created Ordered List" << m_ledAreaListOrdered;
    //

    // Systray
    m_tray = new QSystemTrayIcon(this);
    connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(on_systemTrayActivated(QSystemTrayIcon::ActivationReason)));
    m_tray->setContextMenu(ui->menuBar->findChildren<QMenu*>().first());
    m_tray->setIcon(QIcon(":/img/icon"));
    m_tray->show();
    //

    // Fill Combobox
    connect(ui->comboBox_mode, SIGNAL(currentTextChanged(QString)), this, SLOT(on_modeChanged(QString)));
    ui->comboBox_mode->addItems(QStringList()
                                << "One Fixed Color"
                                << "Individual Fixed Color"
                                << "Worm"
                                << "Flaschendrehen"
                                );

    // Seed for RNG
    qsrand(QTime::currentTime().msec());
    //

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSettings()
{
    qDebug() << this << "Loading Settings";
    QSettings s;

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

void MainWindow::on_updateLEDs()
{
    //qDebug() << this << "Updating LEDs";
    foreach (AtmoLight *al, m_atmoLightList) {
        al->sendLightState();
    }
}

void MainWindow::on_aboutToQuit()
{
    if(m_mode) delete m_mode;
    saveSettings();
}

void MainWindow::on_modeChanged(QString mode)
{
    if(m_mode){
        delete m_mode;
        m_mode = 0;
    }

    //
    if(mode == "One Fixed Color"){
        m_mode = new OneFixedColor(m_ledAreaListOrdered);
    }
    if(mode == "Individual Fixed Color"){
        m_mode = new IndividualFixedColor(m_ledAreaListOrdered);
    }

    if(mode == "Worm"){
        m_mode = new Worm(m_ledAreaListOrdered);
    }

    if(mode == "Flaschendrehen"){
        m_mode = new Flaschendrehen(m_ledAreaListOrdered);
    }
    //
    if(m_mode){
        connect(m_mode, SIGNAL(updateLEDs()), this, SLOT(on_updateLEDs()));
        ui->gridLayout->addWidget(m_mode->widget());

    }

}

void MainWindow::saveSettings()
{
    qDebug() << this << "Saving Settings";
    QSettings s;

}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::instance()->quit();
}
