#include "trainingform.h"
#include "ui_trainingform.h"
#include "mainwindow.h"
#include "settingsform.h"
#include "loggingcategories.h"
#include "header.h"

TrainingForm::TrainingForm(QWidget *parent) : QDialog(parent), ui(new Ui::TrainingForm)
{
    ui->setupUi(this);
    listLineCount = SettingsForm::WordsCount;
    setWindowTitle("Training");
    //деактивировать кнопки
    ui->btmCheck->setEnabled(false);
    ui->btmNext->setEnabled(false);
    //подключаемся к БД
#ifndef QODBC_DATABASE
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
#else
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=data.mdb;");
#endif
    db.setPassword("sqlite18");
    if(!db.open()){
        qDebug(logDebug())<<"TrainingForm: DB open error>";
        qDebug(logDebug())<<"\t"<<db.lastError().text();
    } else {
        qDebug(logDebug())<<"TrainingForm: DB opened";
    }
    //считать все данные
    readAllData();
    //вывести первый тест
    fillLisrs();

    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(SettingsForm::getStyles());
}

TrainingForm::~TrainingForm()
{
    //закрываю соединение
    db.close();
    db.removeDatabase(db.databaseName());
    delete ui;
}

void TrainingForm::setInterfaceLanguage(QString lang)
{
    //установить русский язык
    if(lang == "ru")
    {
        ui->btmCheck->setText("Проверка");
        ui->btmNext->setText("Далее");
        setWindowTitle("Тренировка");
        strEndMsg = "Тест завершился. нажмите ОК для просмотра результата.";
        strTestLbl = "Тест: ";
    }
}

QStringList TrainingForm::result()
{
    int percent = 0;
    if(listLineCount * 3  + ansWrong != 0)
    {
        percent =  (300 * listLineCount) / (listLineCount * 3 + ansWrong);
    }
    // info from https://mgimo.ru/files/89/shkala_ECTS2.htm
    int scorenumber = 2;
    if (percent >= 90) {
        scorenumber  = 5;
    } else if (percent >= 75) {
        scorenumber  = 4;
    } else if (percent >= 60) {
        scorenumber  = 3;
    }

    QJsonObject textObject = QJsonDocument::fromJson(MainWindow::User.toUtf8()).object();
    textObject["date"] = QDate::currentDate().toString(Qt::SystemLocaleShortDate);
    textObject["category"] = "train";
    textObject["score"] = "_____";
    textObject["scorenumber"] = QString::number(scorenumber);
    textObject["percent"] = QString::number(percent);
    textObject["wrong"] = QString::number(ansWrong);
    textObject["right"] = QString::number(ansRight);
    textObject["lang"] = SettingsForm::ApplicationLanguage;
    QStringList res;
    res << QJsonDocument(textObject).toJson(QJsonDocument::Compact);
    qDebug(logDebug()) << "TrainingForm form; WIN32:\t make result JSON";
    qDebug(logDebug()) << "\t\t" << res;
    return res;
}

void TrainingForm::fillDB()
{
    //функция предназначена для перевода текстовой информации и базу
    QFile file("selfnew.txt");
    if(!file.exists())
        return;
#ifndef QODBC_DATABASE
    if(!db.isOpen())
        return;
#endif
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QString strEn, strRu;
        int reating;
        QSqlQuery query = QSqlQuery(db);
        while(!in.atEnd())
        {
            in>>strEn>>reating;
            strRu = in.readLine();
            strRu = strRu.simplified();
            strEn = strEn.simplified();
            QString queryStr = "INSERT INTO favorite (enText , ruText) VALUES('"+strEn+"','"+strRu+"');";
            query.exec(queryStr);
        }
    }
}

void TrainingForm::readAllData()
{
#ifndef QODBC_DATABASE
    if(!db.isOpen())
    {
        qDebug(logDebug())<<"TrainingForm: DB not opened";
        return;
    }
#endif
    //запрос на выделение всего
    QSqlQuery query = QSqlQuery("SELECT * FROM favorite",db);
    //получаю номера колонок
    int enNo = query.record().indexOf("enText");
    int ruNo = query.record().indexOf("ruText");
    int raNo = query.record().indexOf("rating");
    //по очереди вывожу все
    while (query.next())
    {
        data.append(ssint(query.value(enNo).toString(),query.value(ruNo).toString(),query.value(raNo).toInt()));
    }
    //сортирую все данные по рейтингу
    std::sort(data.begin(),data.end(),[](ssint&a,ssint&b){return a.rating<b.rating;});
}

void TrainingForm::fillLisrs()
{
    //очистить оба листа
    ui->list1->clear();
    ui->list2->clear();
    //тесто проводиться в 3 этапа
    //после этого нужно завершить
    if (testConunt-- == 0)
    {
        QMessageBox msg(QMessageBox::NoIcon,"","",QMessageBox::Ok,this,
            Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint) & ~Qt::WindowCloseButtonHint);
        msg.setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
        msg.setText(strEndMsg);
        msg.exec();
        close();
    }
    //обновляем номер теста
    ui->lblLevel->setText(strTestLbl + QString::number(3 - testConunt) + "/3");

    int n = listLineCount, i = 0;
    //выбрать и вывести n элементов которые еще не были показаны
    while (n > 0 && i < data.length())
    {
        //если еще не было показано
        if (!data.at(i).checked)
        {
            //пометить как показанный
            data[i].checked = true;
            //вывести в лист
            ui->list1->addItem(data.at(i).en);
            ui->list2->addItem(data.at(i).ru);
            n--;
        }
        i++;
    }
    //если дошли до конца списка то сбросить список выведенных
    if(i >= data.length())
    {
        for(int j = 0;j<data.length();j++)
        {
            data[j].checked = false;
        }
    }
}

void TrainingForm::on_btmCheck_clicked()
{
    //проверка на правильный выбор
    if(testing())
    {
        //получить указатель на выбранные строки
        QListWidgetItem* item1 = ui->list1->currentItem();
        QListWidgetItem* item2 = ui->list2->currentItem();
        //удалить выбранные элементы
        ui->list1->removeItemWidget(item1);
        ui->list2->removeItemWidget(item2);
        delete item1;
        delete item2;
        //если список уже пуст то отключить кнопки
        if(ui->list1->count() == 0){
            ui->btmCheck->setEnabled(false);
            ui->btmNext->setEnabled(true);
        }
        //правильно ответил
        ansRight++;
    }else {
        //неправильно ответил
        ansWrong++;
    }
    //обновить статус
    ui->labelStatus->setText(QString::number(ansRight)+":"+QString::number(ansWrong));
}

bool TrainingForm::testing()
{
    //если не выбран элемент то выйти
    if(ui->list1->selectedItems().empty() || ui->list2->selectedItems().empty())
        return false;

    //получить текст и вероятный перевод
    QString str1 = ui->list1->currentItem()->text();
    QString str2 = ui->list2->currentItem()->text();

    //искать перевод в списка
    for(int i = 0;i < data.length();i++)
    {
        //если нашел английское слово
        if(data.at(i).en == str1)
        {
            //если перевод совпадает с выбранным
            if(data.at(i).ru == str2)
            {
                // увеличить рейтинг
                data[i].rating++;
                //записать изменения в БД
                changeReatingBD(data.at(i).en, data.at(i).rating);
                return true;
            }else {
                //если перевод не совпадает с выбранным
                //уменьшить рейтинг
                data[i].rating--;
                //записать изменения в БД
                changeReatingBD(data.at(i).en, data.at(i).rating);
                int j = 0;
                //найти неверный перевод в списке
                for(j = 0;j < data.length() && data.at(j).ru != str2;j++);
                //если нашлось
                if(j<data.length())
                {
                    //уменьшить рейтинг
                    data[j].rating--;
                    //записать изменения в БД
                    changeReatingBD(data.at(j).en, data.at(j).rating);
                }
                return false;
            }
        }
    }
    return false;
}


void TrainingForm::changeReatingBD(QString enWord,int val)
{
    //UPDATE table_name SET column1 = value1, column2 = value2, ... WHERE condition;
    //запрос на изменение рейтинга
    QString queryStr = "UPDATE favorite SET rating = " + QString::number(val) + " WHERE enText = '" + enWord + "';";
    QSqlQuery query = QSqlQuery(db);
    if(!query.exec(queryStr))
    {
        qDebug(logDebug())<<"error DB UPDATE";
        qDebug(logDebug())<<"\tquery: "<<queryStr;
    }
}

void TrainingForm::on_btmNext_clicked()
{
    //заполнить листы
    fillLisrs();
    //деактивировать кнопку
    ui->btmNext->setEnabled(false);
}

void TrainingForm::on_list1_clicked(const QModelIndex &)
{
    //при выборе слов активировать кнопку
    ui->btmCheck->setEnabled(!(ui->list1->selectedItems().empty() || ui->list2->selectedItems().empty()));
}

void TrainingForm::on_list2_clicked(const QModelIndex &)
{
    //при выборе слов активировать кнопку
    ui->btmCheck->setEnabled(!(ui->list1->selectedItems().empty() || ui->list2->selectedItems().empty()));
}

void TrainingForm::on_list1_doubleClicked(const QModelIndex &)
{
    //если режим включен, нажимаеться кнопка "проверка"
    //&& если кнопка активна
    if (SettingsForm::testCheckMode == "on" && ui->btmCheck->isEnabled())
    {
        on_btmCheck_clicked();
    }
}

void TrainingForm::on_list2_doubleClicked(const QModelIndex &index)
{
    on_list1_doubleClicked(index);
}
