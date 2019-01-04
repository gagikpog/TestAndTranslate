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
    setStyle(SettingsForm::StyleFilename);
    if(SettingsForm::ApplicationLanguage == "ru")
    {
        ui->btmLanguage->setText("EN");
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
    if(ui->btmLanguage->text() == "EN")
        trForm->setInterfaceLanguage();
    trForm->setStyleSheet(loadStyle(SettingsForm::StyleFilename));
    this->hide();
    trForm->exec();
    this->show();
}

void MainWindow::on_btmLanguage_clicked()
{
    if(ui->btmLanguage->text() == "EN")
    {
        ui->btmLanguage->setText("РУ");
        setInterfaceLanguage("en");
        SettingsForm::ApplicationLanguage = "en";
    }  else {
        ui->btmLanguage->setText("EN");
        setInterfaceLanguage("ru");
        SettingsForm::ApplicationLanguage = "ru";
    }
    SettingsForm::writeLanguage();
}

void MainWindow::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->btmExit->setText("Выход");
        ui->btmSetting->setText("Настройки");
        ui->btmTraining->setText("Тренировка");
        ui->btmTranslate->setText("Переводчик");
    }else {
        ui->btmExit->setText("Exit");
        ui->btmSetting->setText("Settings");
        ui->btmTraining->setText("Training");
        ui->btmTranslate->setText("Translate");
    }
}

QString MainWindow::loadStyle(QString filename)
{
    QFile* file = new QFile(filename);
    if(!file->exists())
        return "";
    file->open(QIODevice::ReadOnly);
    QTextStream* in = new QTextStream(file);
    QString res = in->readAll();
    file->close();
    return res;
}

void MainWindow::on_btmTraining_clicked()
{
    TrainingForm *trForm = new TrainingForm();
    if(ui->btmLanguage->text() == "EN")
        trForm->setInterfaceLanguage();
    trForm->setStyleSheet(loadStyle(SettingsForm::StyleFilename));
    this->hide();
    trForm->exec();
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    ConstructorForm *form = new ConstructorForm();
    if(ui->btmLanguage->text() == "EN")
        form->setInterfaceLanguage();
    form->setStyleSheet(loadStyle(SettingsForm::StyleFilename));
    this->hide();
    form->exec();
    this->show();
}

void MainWindow::on_btmSetting_clicked()
{
    SettingsForm *form = new SettingsForm();
    if(ui->btmLanguage->text() == "EN")
        form->setInterfaceLanguage();
    this->hide();
    form->exec();
    setStyle(SettingsForm::StyleFilename);
    this->show();
}

void MainWindow::setStyle(QString filename)
{
    ui->centralWidget->setStyleSheet(styleSheet());
    ui->centralWidget->setStyleSheet(loadStyle(filename));
}
