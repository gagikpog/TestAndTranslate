#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translateform.h"
#include "trainingform.h"
#include "constructorform.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    }  else {
        ui->btmLanguage->setText("EN");
        setInterfaceLanguage();
    }
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

void MainWindow::on_btmTraining_clicked()
{
    TrainingForm *trForm = new TrainingForm();
    if(ui->btmLanguage->text() == "EN")
        trForm->setInterfaceLanguage();
    this->hide();
    trForm->exec();
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    ConstructorForm *form = new ConstructorForm();
    if(ui->btmLanguage->text() == "EN")
        form->setInterfaceLanguage();
    this->hide();
    form->exec();
    this->show();
}
