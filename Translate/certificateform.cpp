#include "certificateform.h"
#include "ui_certificateform.h"
#include "mainwindow.h"

CertificateForm::CertificateForm(QWidget *parent) : QDialog(parent), ui(new Ui::CertificateForm)
{
    ui->setupUi(this);
    setWindowTitle("Certificate");
    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(SettingsForm::getStyles());
}

CertificateForm::~CertificateForm()
{
    delete ui;
}

void CertificateForm::loadCertificate(QString jsonData)
{
    QString fname = "certificateRU.html";
    if(SettingsForm::ApplicationLanguage == "en")
        fname = "certificateEN.html";

    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug(logDebug())<<"html file not find";
        return;
    }

    QTextStream fin(&file);
    QString htmlData = fin.readAll();

    file.close();
    QJsonObject usr = QJsonDocument::fromJson(MainWindow::User.toUtf8()).object();

    /*_NAME_  _SURNAME_  _GROUP_  _DATE_  _CATEGORY_  _SCORE_ _SCORENUMBER_  _PERCENT_  _WRONG_  _RIGHT_
    */
    htmlData.replace("_NAME_",usr.value("name").toString());
    htmlData.replace("_SURNAME_",usr.value("sname").toString());
    htmlData.replace("_GROUP_",usr.value("group").toString());
    htmlData.replace("_DATE_",QDate::currentDate().toString(Qt::SystemLocaleShortDate));

    /////
    QJsonObject inf = QJsonDocument::fromJson(jsonData.toUtf8()).object();
    htmlData.replace("_CATEGORY_",usr.value("category").toString());
    htmlData.replace("_SCORE_",usr.value("score").toString());
    htmlData.replace("_SCORENUMBER_",usr.value("scoreNumber").toString());
    htmlData.replace("_PERCENT_",usr.value("percent").toString());
    htmlData.replace("_WRONG_",usr.value("wrong").toString());
    htmlData.replace("_RIGHT_",usr.value("right").toString());

    ui->webView->setHtml(htmlData.toUtf8());
}

void CertificateForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->btmClose->setText("&Выход");
        ui->btmSave->setText("&Сохранить");
        setWindowTitle("Сертификат");
        strSave = "Сохранить";
    }
}

void CertificateForm::on_btmSave_clicked()
{
    QFileDialog dlg;
    dlg.setDefaultSuffix(".pdf");
    QString filename = dlg.getSaveFileName(this,strSave, "", tr("PDF Files (*.pdf)"));
    if(filename.isEmpty())
        return;

    if(!filename.endsWith(".pdf"))
        filename += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFileName(filename);

    ui->webView->print(&printer);
}
