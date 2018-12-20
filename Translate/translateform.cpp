#include "translateform.h"
#include "ui_translateform.h"

TranslateForm::TranslateForm(QWidget *parent) : QDialog(parent), ui(new Ui::TranslateForm)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    ReadDB();
}

TranslateForm::~TranslateForm()
{
    //закрываю соединение
    db.close();
    db.removeDatabase("data.db");
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
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("data.db");
    if(db.open())
    {
        //запрос на выделение всего
        QSqlQuery query = QSqlQuery("SELECT * FROM favorite",db);
        //получаю номера колонок
        int enNo = query.record().indexOf("enText");
        int ruNo = query.record().indexOf("ruText");
        //int raNo = query.record().indexOf("rating");
       //по очереди вывожу все
        int i = 0;
        while (query.next())
        {
            i++;
            ui->tableWidget->setRowCount(i);
            QTableWidgetItem *itemEN = new QTableWidgetItem (query.value(enNo).toString());
            QTableWidgetItem *itemRU = new QTableWidgetItem (query.value(ruNo).toString());
            ui->tableWidget->setItem(i-1,0,itemEN);
            ui->tableWidget->setItem(i-1,1,itemRU);
        }
    }
}


void TranslateForm::on_btmLanguage_clicked()
{
    //переключить перевод языков
    if(TranslateLanguage == "ru")
    {
        TranslateLanguage = "en";
        ui->label1->setText("Russian");
        ui->label2->setText("English");
    }else {
        TranslateLanguage = "ru";
        ui->label1->setText("English");
        ui->label2->setText("Russian");
    }
    QString tmp = ui->msgOutput->text();
    ui->msgOutput->setText(ui->msgInput->text());
    ui->msgInput->setText(tmp);
}

void TranslateForm::on_btmFavorite_clicked()
{
    QString txt1,txt2;
    txt1 = ui->msgInput->text();
    txt2 = ui->msgOutput->text();
    if( txt1 != "" && txt2 != "")
    {
        if(TranslateLanguage == "en")
            txt1.swap(txt2);

        if(db.open())
        {
            if(!ui->tableWidget->findItems(txt1,0).empty())
            {
                QMessageBox msgBox;
                msgBox.setText("The word has already been added");
                msgBox.exec();
                return;
            }
            QString queryStr = "INSERT INTO favorite (enText , ruText) VALUES('"+txt1+"','"+txt2+"');";
            //
            QSqlQuery query = QSqlQuery(db);
            if(query.exec(queryStr))
            {
                ui->msgInput->setText("");
                ui->msgOutput->setText("");
            }
            ReadDB();
        }
    }

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
    on_btmTranslate_clicked();
}

void TranslateForm::on_btmRemove_clicked()
{
    if(db.open())
    {
        QModelIndexList indexList = ui->tableWidget->selectionModel()->selectedIndexes();
        if(!indexList.empty())
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Message");
            msgBox.setText("Do you really want to delete this word?");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::No)
                return;
            QString str =  ui->tableWidget->item(indexList.at(0).row(),0)->text();
            QString queryStr = "DELETE FROM favorite WHERE enText='"+str+"';";
            //
            QSqlQuery query = QSqlQuery(db);
            if(query.exec(queryStr))
            {
                ui->msgInput->setText("");
                ui->msgOutput->setText("");
            }
            ReadDB();
        }
    }
}

void TranslateForm::resizeEvent(QResizeEvent*)
{
    ui->tableWidget->setColumnWidth(0,(width()-20)/2);
}
