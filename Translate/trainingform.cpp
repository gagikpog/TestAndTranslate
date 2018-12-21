#include "trainingform.h"
#include "ui_trainingform.h"
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

TrainingForm::TrainingForm(QWidget *parent) : QDialog(parent), ui(new Ui::TrainingForm)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    //fillDB();
    readAllData();
    fillLisrs();
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

void TrainingForm::setInterfaceLanguage()
{

}

void TrainingForm::fillDB()
{
    QFile file("selfnew.txt");
    if(!file.exists())
        return;
    if(file.open(QIODevice::ReadOnly) && db.open())
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
    if(db.open())
    {
        //запрос на выделение всего
        QSqlQuery query = QSqlQuery("SELECT * FROM favorite",db);
        //получаю номера колонок
        int enNo = query.record().indexOf("enText");
        int ruNo = query.record().indexOf("ruText");
        int raNo = query.record().indexOf("rating");
        //по очереди вывожу все
        while (query.next())
            data.append(ssint(query.value(enNo).toString(),query.value(ruNo).toString(),query.value(raNo).toInt()));
    }
}

void TrainingForm::fillLisrs()
{
    ui->list1->clear();
    ui->list2->clear();
    int n = listLineCount,i = 0;
    while(n>0 && i < data.length())
    {
        if(!data.at(i).checked)
        {
            data[i].checked = true;
            ui->list1->addItem(data.at(i).en);
            ui->list2->addItem(data.at(i).ru);
        }
        n--;
        i++;
    }
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
    if(testing())
    {
        QListWidgetItem* item1 = ui->list1->currentItem();
        QListWidgetItem* item2 = ui->list2->currentItem();
        ui->list1->removeItemWidget(item1);
        ui->list2->removeItemWidget(item2);
        delete item1;
        delete item2;
    }
}

bool TrainingForm::testing()
{
    QString str1 = ui->list1->currentItem()->text();
    QString str2 = ui->list2->currentItem()->text();

    for(int i = 0;i < data.length();i++)
    {
        if(data.at(i).en == str1)
        {
            if(data.at(i).ru == str2)
            {
                data[i].rating++;
                changeReatingBD(data.at(i).en, data.at(i).rating);
                return true;
            }else {
                data[i].rating--;
                changeReatingBD(data.at(i).en, data.at(i).rating);
                int j = 0;
                for(j = 0;j < data.length() && data.at(j).ru != str2;j++);
                if(j<data.length())
                {
                    data[j].rating--;
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
    QString queryStr = "UPDATE favorite SET rating = " + QString::number(val) + " WHERE enText = '" + enWord + "';";
    QSqlQuery query = QSqlQuery(db);
    if(!query.exec(queryStr))
    {
        qDebug()<<"error DB UPDATE";
    }

}
