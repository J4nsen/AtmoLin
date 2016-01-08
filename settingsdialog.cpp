#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QSettings>
#include <QListWidgetItem>
#include <QDebug>
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    loadAtmoLightsFromSettings();
    connect(this, SIGNAL(finished(int)), this, SLOT(on_finished(int)));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::loadAtmoLightsFromSettings()
{
    qDebug() << this << "Loading Atmolights";
    QSettings s;
    s.beginGroup("AtmoLights");
    QStringList keys = s.childGroups();

    foreach(QString key, keys){
        s.beginGroup(key);
        QString port = s.value("port", "").toString();
        QStringList orderAsStrings = s.value("order").toStringList();

        atmoLightDevice ald;
        ald.serialPortName = port;
        ald.ledOrder = orderAsStrings;
        m_atmolightDeviceList[port] = ald;
        s.endGroup();
    }

    refreshList();
}

void SettingsDialog::refreshList()
{
    ui->listWidget->clear();
    foreach (atmoLightDevice ald, m_atmolightDeviceList) {
        QListWidgetItem *item = new QListWidgetItem(ald.serialPortName);
        ui->listWidget->addItem(item);
    }
}

void SettingsDialog::on_pushButton_add_clicked()
{
    atmoLightDevice ald;
    ald.serialPortName = ui->lineEdit_portName->text();
    ald.ledOrder << ui->lineEdit_order->text().split(",");
    m_atmolightDeviceList[ald.serialPortName] = ald;

    refreshList();
}

void SettingsDialog::on_finished(int exitCode)
{
    // Cancel
    if(!exitCode) return;

    // Ok
    QSettings s;
    s.beginGroup("AtmoLights");
    foreach (atmoLightDevice ald, m_atmolightDeviceList) {
        s.beginGroup(ald.serialPortName);
        s.setValue("port", ald.serialPortName);
        s.setValue("order", ald.ledOrder);
        s.endGroup();
    }
    s.endGroup();
}

void SettingsDialog::on_listWidget_currentTextChanged(const QString &currentText)
{
    atmoLightDevice ald = m_atmolightDeviceList[currentText];
    ui->lineEdit_portName->setText(ald.serialPortName);
    ui->lineEdit_order->setText(ald.ledOrder.join(","));
}

void SettingsDialog::on_pushButton_delete_clicked()
{
    if(ui->listWidget->currentItem()){
        m_atmolightDeviceList.remove(ui->listWidget->currentItem()->text());
    }
    refreshList();
}
