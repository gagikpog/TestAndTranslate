#include "translateform.h"
#include "ui_translateform.h"
#include <QNetworkReply>
#include <QRegularExpression>
#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

TranslateForm::TranslateForm(QWidget *parent) : QDialog(parent), ui(new Ui::TranslateForm)
{
    ui->setupUi(this);
}

TranslateForm::~TranslateForm()
{
    delete ui;
}

//процедура которая вызывается для приема ответа от сервера
void TranslateForm::replyFinished(QNetworkReply* reply)
{
    //преобразование полученных данных в массив байт
    QByteArray response = reply->readAll();
    //получаем из его Q строку
    QString DataAsString = QString::fromStdString(response.toStdString());
    //далее отрезаем из строки лишнее и оставляем только перевод
    //используем для этого регулярные выражения
    QString pattern = "\"text\":\\[.*\"\\]";//ui->lineEdit->text();
    QRegExp regex(pattern);
    if (regex.indexIn(DataAsString) < 0)
    {
        //перевод не найден
        ui->msgOutput->setText("not translate");
        return;
    }
    QString res = regex.cap(0);
    res = res.left(res.length()-2);
    res = res.right(res.length()-9);
    //вывод результата
    ui->msgOutput->setText(res);
}

//процедура читает из таблицы все и выводит на экран
void TranslateForm::ReadDB()
{
    //создаем подключение к БД
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(db.open())
    {
        //очистить список
        ui->listWidget->clear();
        //запрос на выделение всего
        QSqlQuery query = QSqlQuery("SELECT * FROM favorite",db);
        //получаю номера колонок
        int enNo = query.record().indexOf("enText");
        int ruNo = query.record().indexOf("ruText");
        int raNo = query.record().indexOf("rating");
       //по очереди вывожу все
        while (query.next()) {
            QString str = query.value(enNo).toString();
            str += " " + query.value(ruNo).toString();
            str += " " + query.value(raNo).toString();
            ui->listWidget->addItem(str);
        }
        //закрываю соединение
        db.close();
        db.removeDatabase("data.db");
    }
}


void TranslateForm::on_btmLanguage_clicked()
{
    //переключить перевод языков
    if(TranslateLanguage == "ru")
    {
        TranslateLanguage = "en";
        ui->btmLanguage->setText("EN-РУ");
    }else {
        TranslateLanguage = "ru";
        ui->btmLanguage->setText("РУ-EN");
    }
}

void TranslateForm::on_btmFavorite_clicked()
{
    ReadDB();
}

void TranslateForm::on_btmTranslate_clicked()
{
    //готовлюсь к отправке запроса
    QNetworkAccessManager *NAM = new QNetworkAccessManager(this);
    //назначаю процедуру для подучения ответа
    connect(NAM, SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    //это мой личный ключ. НЕ ТРОГАТЬ!
    QString myYandexKey = "trnsl.1.1.20181218T063705Z.c1ca51e673146583.e557c8ab73bfc914cc1311dc2ec7646f9b1fa50f";
    //то что нужно переводить
    QString translateText = ui->msgInput->text();
    //нечего переводить
    if(translateText == "")
    {
        ui->msgOutput->setText("");
        return;
    }
    //сервер Яндекса который за меня будет переводить
    QString host = "https://translate.yandex.net/api/v1.5/tr.json/translate";
    //отправляю get запрос
    NAM->get(QNetworkRequest(QUrl(host+"?key="+myYandexKey+"&text="+translateText+"&lang="+TranslateLanguage)));
}

void TranslateForm::on_msgInput_returnPressed()
{
    //при нажатии на "Enter" запускается перевод
    //on_btmTranslate_clicked();
}
