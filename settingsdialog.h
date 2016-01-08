#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_pushButton_add_clicked();
    void on_finished(int exitCode);

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_pushButton_delete_clicked();

private:
    Ui::SettingsDialog *ui;
    void loadAtmoLightsFromSettings();
    void refreshList();

    struct atmoLightDevice{
        QString name;
        QString serialPortName;
        QStringList ledOrder;

    };

    QHash<QString, atmoLightDevice> m_atmolightDeviceList;
};

#endif // SETTINGSDIALOG_H
