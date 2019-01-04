#include "settingsform.h"
#include "ui_settingsform.h"
#include "mainwindow.h"
#include <QSettings>

 QString SettingsForm::StyleFilename = "Styles/dark.qss";
 const QString SettingsForm::settingsFilename = "settings.ini";

SettingsForm::SettingsForm(QWidget *parent) :QDialog(parent), ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    readLocakSettings();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {

    }
}

void SettingsForm::readSettings()
{
    QSettings settings(settingsFilename, QSettings::NativeFormat);
    StyleFilename = settings.value("styleFile", "").toString();
}

void SettingsForm::on_btmStyle_clicked()
{
    writeSettings();
}

void SettingsForm::writeSettings()
{
    QString check = "dark";
    if(ui->rBtmLight->isChecked())
        check = "light";
    if(ui->rBtmCustom->isChecked())
        check = "custom";

    QSettings settings(settingsFilename, QSettings::NativeFormat);
    settings.setValue("styleFile", StyleFilename);
    settings.setValue("checkbux",check );
}

void SettingsForm::readLocakSettings()
{
    QSettings settings(settingsFilename, QSettings::NativeFormat);
    QString check = settings.value("checkbux", "").toString();

    ui->rBtmCustom->setChecked(check == "custom");
    ui->rBtmDark->setChecked(check == "dark");
    ui->rBtmLight->setChecked(check == "light");
    ui->btmStyle->setEnabled(check == "custom");

}

void SettingsForm::on_rBtmCustom_clicked(bool checked)
{
    ui->btmStyle->setEnabled(checked);
    //setStyleSheet(MainWindow::loadStyle(StyleFilename));
    //writeSettings();
}

void SettingsForm::on_rBtmLight_clicked(bool checked)
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = "Styles/light.qss";
    setStyleSheet(MainWindow::loadStyle(StyleFilename));
    writeSettings();
}

void SettingsForm::on_rBtmDark_clicked(bool checked)
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = "Styles/dark.qss";
    setStyleSheet(MainWindow::loadStyle(StyleFilename));
    writeSettings();
}
