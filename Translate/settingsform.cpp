#include "settingsform.h"
#include "sentencemanagerform.h"
#include "ui_settingsform.h"
#include "mainwindow.h"
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

 QString SettingsForm::StyleFilename = "Styles/dark.qss";
 QString SettingsForm::ApplicationLanguage = "en";
 const QString SettingsForm::settingsFilename = "settings.ini";


SettingsForm::SettingsForm(QWidget *parent) :QDialog(parent), ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    readLocakSettings();
    setStyleSheet(MainWindow::loadStyle(StyleFilename));
    setInterfaceLanguage(ApplicationLanguage);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->rBtmDark->setText("Темный");
        ui->rBtmLight->setText("Светлая");
        ui->rBtmCustom->setText("Другой");
        ui->rBtmDefoult->setText("По умолчанию");
        ui->btmStyle->setText("Загрузить стиль");
    }
}

void SettingsForm::readSettings()
{
    QSettings settings(settingsFilename, QSettings::IniFormat);
    StyleFilename = settings.value("styleFile", "").toString();
    ApplicationLanguage = settings.value("language", "").toString();
}

void SettingsForm::writeLanguage()
{
    QSettings settings(settingsFilename, QSettings::IniFormat);
    settings.setValue("language", ApplicationLanguage);
}

void SettingsForm::on_btmStyle_clicked()
{
    QFileDialog* dlg = new QFileDialog(this);
    QString res = dlg->getOpenFileName(this,"caption","Styles","Qt style files(*.qss);; All files (*.*)");
    if(res != "")
    {
        StyleFilename = res;
        setStyleSheet(MainWindow::loadStyle(StyleFilename));
        writeSettings();
        selectedRadioBtm = "custom";
    }else {
        selectRadioBatton(selectedRadioBtm);
    }
}

void SettingsForm::writeSettings()
{
    QString check = "dark";
    if(ui->rBtmLight->isChecked())
        check = "light";
    if(ui->rBtmCustom->isChecked())
        check = "custom";
    if(ui->rBtmDefoult->isChecked())
        check = "defoult";

    QSettings settings(settingsFilename, QSettings::IniFormat);
    settings.setValue("styleFile", StyleFilename);
    settings.setValue("checkbux",check );
}

void SettingsForm::readLocakSettings()
{
    QSettings settings(settingsFilename, QSettings::IniFormat);
    selectRadioBatton(settings.value("checkbux", "").toString());
}

void SettingsForm::selectRadioBatton(QString check)
{
    ui->rBtmDefoult->setChecked(check == "defoult");
    ui->rBtmCustom->setChecked(check == "custom");
    ui->rBtmDark->setChecked(check == "dark");
    ui->rBtmLight->setChecked(check == "light");
    ui->btmStyle->setEnabled(check == "custom");
    selectedRadioBtm = check;
}

void SettingsForm::on_rBtmCustom_clicked(bool checked)
{
    ui->btmStyle->setEnabled(checked);
    on_btmStyle_clicked();
}

void SettingsForm::on_rBtmLight_clicked(bool )
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = "Styles/light.qss";
    setStyleSheet(MainWindow::loadStyle(StyleFilename));
    writeSettings();
    selectedRadioBtm = "light";
}

void SettingsForm::on_rBtmDark_clicked(bool )
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = "Styles/dark.qss";
    setStyleSheet(MainWindow::loadStyle(StyleFilename));
    writeSettings();
    selectedRadioBtm = "dark";
}

void SettingsForm::on_rBtmDefoult_clicked(bool )
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = "";
    setStyleSheet(MainWindow::loadStyle(StyleFilename));
    writeSettings();
    selectedRadioBtm = "defoult";
}

void SettingsForm::on_btmSManager_clicked()
{
    SentenceManagerForm *form = new SentenceManagerForm();
    //this->hide();
    form->exec();
    //this->show();
}
