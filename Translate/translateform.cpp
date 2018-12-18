#include "translateform.h"
#include "ui_translateform.h"
#include <QNetworkReply>
#include <QRegularExpression>
#include <QString>

TranslateForm::TranslateForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TranslateForm)
{
    ui->setupUi(this);
}

TranslateForm::~TranslateForm()
{
    delete ui;
}

void TranslateForm::on_pushButton_clicked()
{
    QNetworkAccessManager *NAM = new QNetworkAccessManager(this);
    connect(NAM, SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    QString myYandexKey = "trnsl.1.1.20181218T063705Z.c1ca51e673146583.e557c8ab73bfc914cc1311dc2ec7646f9b1fa50f";
    QString translateText = ui->msgInput->text();
    if(translateText == "")
    {
        ui->msgOutput->setText("");
        return;
    }
    NAM->get(QNetworkRequest(QUrl("https://translate.yandex.net/api/v1.5/tr.json/translate?key="+myYandexKey+"&text="+translateText+"&lang=ru")));
}

void TranslateForm::replyFinished(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    QString DataAsString = QString::fromStdString(response.toStdString());
    QString pattern = "\"text\":\\[.*\"\\]";//ui->lineEdit->text();
    QRegExp regex(pattern);
    if (regex.indexIn(DataAsString) < 0)
    {
        ui->msgOutput->setText("not translate");
        return;
    }
    QString res = regex.cap(0);
    res = res.left(res.length()-2);
    res = res.right(res.length()-9);
    ui->msgOutput->setText(res);
}

void TranslateForm::on_msgInput_returnPressed()
{
    on_pushButton_clicked();
}
