#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translateform.h"
#include "trainingform.h"
#include "constructorform.h"
#include "settingsform.h"
#include "authenticationform.h"
#include "loggingcategories.h"
#ifdef __linux__
#include "certificateform.h"
#endif
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
    qDebug(logDebug()) << "MainWindow destroyed: call update chacker";
    QString version = SettingsForm::checkUpdate("hd");
    qDebug(logDebug()) << "MainWindow destroyed: " << version;
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
    if (lang == "ru")
    {
        ui->btmExit->setText("&Выход");
        ui->btmSetting->setText("&Настройки");
        ui->btmTraining->setText("&Тренировка");
        ui->btmTranslate->setText("&Переводчик");
        ui->btmPuzzle->setText("П&азл");
        setWindowTitle("Меню");
        if(User.isEmpty())
        {
            ui->lblUser->setText("<a href=\"whatever\">Гость</a>");
        }
    } else {
        ui->btmExit->setText("&Close");
        ui->btmSetting->setText("&Settings");
        ui->btmTraining->setText("Training");
        ui->btmTranslate->setText("&Translate");
        ui->btmPuzzle->setText("&Puzzle");
        setWindowTitle("Menu");
        if (User.isEmpty())
        {
            ui->lblUser->setText("<a href=\"whatever\">Visitor</a>");
        }

    }
}

void MainWindow::on_btmTraining_clicked()
{
    if(!UserAuth())
        return;
    TrainingForm* trForm = new TrainingForm();
    this->hide();
    trForm->exec();
    this->show();
#ifdef __linux__
    CertificateForm* cf = new CertificateForm(this);
    cf->loadCertificate("");
    cf->exec();
#else
    QJsonObject textObject = QJsonDocument::fromJson(User.toUtf8()).object();
    QString tmp = textObject.value("group").toString();
    if(tmp == "sqlite18")
    {
         return;
    }
    qDebug(logDebug()) << "mainwindow form; WIN32; Training result:\t Calling show.exe";
    QString prog = QDir::currentPath() + "/show.exe";
    QProcess* process = new QProcess(this);
    process->start(prog, trForm->result());
#endif
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
#ifdef __linux__
    CertificateForm* cf = new CertificateForm(this);
    cf->loadCertificate("");
    cf->exec();
#else
   QJsonObject textObject = QJsonDocument::fromJson(User.toUtf8()).object();
   QString tmp = textObject.value("group").toString();
   if(tmp == "sqlite18")
   {
        return;
   }
   qDebug(logDebug()) << "mainwindow form; WIN32; Puzzle result:\t Calling show.exe";
   QString prog = QDir::currentPath() + "/show.exe";
   qDebug(logDebug()) << "programm: " << prog;
   QProcess* process = new QProcess(this);
   process->start(prog, form->result());
#endif
}

bool MainWindow::UserAuth(bool fo)
{
    tmr->stop();
    if(!User.isEmpty() && !fo)
    {
        return true;
    }

    AuthenticationForm* f = new AuthenticationForm();
    f->exec();
    if(f->isAuth())
    {
        User = f->getAuthData();
        qDebug(logDebug())<<"MainWindow: username";
        qDebug(logDebug())<<"\t"<<User;
        QJsonObject root = QJsonDocument::fromJson(User.toUtf8()).object();
        ui->lblUser->setText("<a href=\"whatever\">"+root.value("name").toString()+" "+root.value("sname").toString()+"</a>");
    } else {
        return false;
    }
    return true;
}

void MainWindow::on_lblUser_linkActivated(const QString &)
{
    UserAuth(true);
}
