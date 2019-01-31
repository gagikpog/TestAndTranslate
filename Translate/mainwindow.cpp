#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translateform.h"
#include "trainingform.h"
#include "constructorform.h"
#include "settingsform.h"
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "authenticationform.h"

QString MainWindow::User;

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
    tmr = new QTimer();
    tmr->setInterval(500);
    connect(tmr, SIGNAL(timeout()), this, SLOT(UserAuth()));
    tmr->start();

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
        ui->btmPuzzle->setText("П&азл");
    }else {
        ui->btmExit->setText("&Close");
        ui->btmSetting->setText("&Settings");
        ui->btmTraining->setText("Training");
        ui->btmTranslate->setText("&Translate");
        ui->btmPuzzle->setText("&Puzzle");
    }
}

void MainWindow::on_btmTraining_clicked()
{
    if(!UserAuth())
        return;
    TrainingForm *trForm = new TrainingForm();
    this->hide();
    trForm->exec();
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

void MainWindow::on_btmPuzzle_clicked()
{
    if(!UserAuth())
        return;
    ConstructorForm *form = new ConstructorForm();
    this->hide();
    form->exec();
    this->show();
}

bool MainWindow::UserAuth()
{
    tmr->stop();
    if(!User.isEmpty())
        return true;

    AuthenticationForm* f = new AuthenticationForm();
    f->exec();
    if(f->isAuth())
    {
        User = f->getAuthData();
        QJsonObject root = QJsonDocument::fromJson(QByteArray(User.toUtf8(),1000)).object();
        ui->lblUser->setText(root.value("name").toString()+" "+root.value("sname").toString());
    } else {
        return false;
    }
    return true;
}
