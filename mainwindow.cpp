#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ledarea.h"
#include <color_wheel.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AtmoLight *al = new AtmoLight("/dev/atmolight-right");

    al->connectToBoard();
    al->sendLightState();
    m_atmoLightList.append(al);

    al = new AtmoLight("/dev/atmolight-left");

    al->connectToBoard();
    al->sendLightState();
    m_atmoLightList.append(al);

    color_widgets::ColorWheel *cw = new color_widgets::ColorWheel();
    ui->gridLayout->addWidget(cw);

    connect(cw, SIGNAL(colorChanged(QColor)), this, SLOT(on_colorChanged(QColor)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
