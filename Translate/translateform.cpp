#include "translateform.h"
#include "ui_translateform.h"

TranslateForm::TranslateForm(QWidget *parent) : QDialog(parent), ui(new Ui::TranslateForm)
{
    ui->setupUi(this);
    setWindowTitle("Translator");
    //открываем соединение с базой
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    //заполнить таблицу
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
            //добавить строку в таблице
            ui->tableWidget->setRowCount(i);
            //создаю колонку
            QTableWidgetItem *itemEN = new QTableWidgetItem (query.value(enNo).toString());
            QTableWidgetItem *itemRU = new QTableWidgetItem (query.value(ruNo).toString());
            //добавляю его в таблицу
            ui->tableWidget->setItem(i-1,0,itemEN);
            ui->tableWidget->setItem(i-1,1,itemRU);
        }
    }
}


void TranslateForm::on_btmLanguage_clicked()
{
    //переключить перевод языков
    if(TranslateLanguage == "ru")
        TranslateLanguage = "en";
    else TranslateLanguage = "ru";
    //swap названий
    QString tmp = ui->msgOutput->text();
    ui->msgOutput->setText(ui->msgInput->text());
    ui->msgInput->setText(tmp);
    //swap названий
    tmp = ui->label1->text();
    ui->label1->setText(ui->label2->text());
    ui->label2->setText(tmp);
    //сделать перевод
    on_btmTranslate_clicked();
}

void TranslateForm::on_btmFavorite_clicked()
{
    //берем слова для добавления в избранные
    QString txt1,txt2;
    txt1 = ui->msgInput->text();
    txt2 = ui->msgOutput->text();
    //проверка на простоту строк
    if( txt1 != "" && txt2 != "")
    {
        //если с русского на английский меняем местами слова
        if(TranslateLanguage == "en")
            txt1.swap(txt2);

        if(db.open())
        {
            //если слово уже добавлена предупреждаю и выхожу
            if(!ui->tableWidget->findItems(txt1,0).empty())
            {
                QMessageBox msgBox;
                msgBox.setText("The word has already been added");
                msgBox.exec();
                return;
            }
            //запрос на добавления
            QString queryStr = "INSERT INTO favorite (enText , ruText) VALUES('"+txt1+"','"+txt2+"');";
            //
            QSqlQuery query = QSqlQuery(db);
            if(query.exec(queryStr))
            {
                //если слово успешно добавлена очистить поля
                ui->msgInput->setText("");
                ui->msgOutput->setText("");
            }
            //обновить таблицу
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
    //при нажатии на Enter переводить
    on_btmTranslate_clicked();
}

void TranslateForm::on_btmRemove_clicked()
{
    //удаление записи из базы
    if(db.open())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(msgBoxTitle);
        //получаю список выделенных ячеек
        QModelIndexList indexList = ui->tableWidget->selectionModel()->selectedIndexes();
        //если ничего не выделено то выходим
        if(indexList.empty())
        {
            msgBox.setText(msgBoxWarning);
            msgBox.exec();
            return;
        }
        //ожидание  подтверждение на удаление
        msgBox.setText(msgBoxQuestion);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        //не удалить
        if(msgBox.exec() == QMessageBox::No)
            return;
        //получить выделенную строку
        QString str =  ui->tableWidget->item(indexList.at(0).row(),0)->text();
        //запрос на удаление
        QString queryStr = "DELETE FROM favorite WHERE enText='"+str+"';";
        //выполнить запрос
        QSqlQuery query = QSqlQuery(db);
        query.exec(queryStr);
        //обновить таблицу
        ReadDB();
    }
}

void TranslateForm::resizeEvent(QResizeEvent*)
{
    //ширину первой колонки сделать половины ширины окна
    ui->tableWidget->setColumnWidth(0,(width()-20)/2);
}

void TranslateForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->btmFavorite->setText("Добавить в избранные");
        ui->btmRemove->setText("Удалить");
        ui->btmTranslate->setText("Перевести");
        ui->label1->setText("Английский");
        ui->label2->setText("Русский");
        ui->tableWidget->horizontalHeaderItem(0)->setText("Английский");
        ui->tableWidget->horizontalHeaderItem(1)->setText("Русский");
        msgBoxWarning = "Выберите пожалуйста слово для удаления!";
        msgBoxQuestion = "Вы действительно хотите удалить это слово?";
        msgBoxTitle = "Сообщение";
        setWindowTitle("Переводчик");
    }
}

void TranslateForm::on_btmClear_clicked()
{
    ui->msgInput->setText("");
    ui->msgOutput->setText("");
}
