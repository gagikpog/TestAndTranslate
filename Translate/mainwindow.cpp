#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translateform.h"
#include "trainingform.h"
#include "constructorform.h"
#include "settingsform.h"
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SettingsForm::readSettings();
    ui->centralWidget->setStyleSheet(SettingsForm::getStyles());
    if(SettingsForm::ApplicationLanguage == "ru")
    {
        ui->btmLanguage->setText("&EN");
        setInterfaceLanguage("ru");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btmTranslate_clicked()
{
    TranslateForm *trForm = new TranslateForm();
    this->hide();
    trForm->exec();
    this->show();
}

void MainWindow::on_btmLanguage_clicked()
{
    if(ui->btmLanguage->text() == "&EN")
    {
        ui->btmLanguage->setText("&РУ");
        setInterfaceLanguage("en");
        SettingsForm::ApplicationLanguage = "en";
    }  else {
        ui->btmLanguage->setText("&EN");
        setInterfaceLanguage("ru");
        SettingsForm::ApplicationLanguage = "ru";
    }
    SettingsForm::writeLanguage();
}

void MainWindow::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->btmExit->setText("&Выход");
        ui->btmSetting->setText("&Настройки");
        ui->btmTraining->setText("&Тренировка");
        ui->btmTranslate->setText("&Переводчик");
    }else {
        ui->btmExit->setText("&Close");
        ui->btmSetting->setText("&Settings");
        ui->btmTraining->setText("Training");
        ui->btmTranslate->setText("&Translate");
    }
}



void MainWindow::on_btmTraining_clicked()
{
    TrainingForm *trForm = new TrainingForm();
    this->hide();
    trForm->exec();
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    ConstructorForm *form = new ConstructorForm();
    this->hide();
    form->exec();
    this->show();
}

void MainWindow::on_btmSetting_clicked()
{
    SettingsForm *form = new SettingsForm();
    this->hide();
    form->exec();
    ui->centralWidget->setStyleSheet(SettingsForm::getStyles());
    this->show();
}
