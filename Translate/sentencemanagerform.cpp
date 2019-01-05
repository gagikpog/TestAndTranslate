#include "sentencemanagerform.h"
#include "ui_sentencemanager.h"

SentenceManagerForm::SentenceManagerForm(QWidget *parent) :QDialog(parent), ui(new Ui::SentenceManager)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setPassword("sqlite18");
    db.open();
}

SentenceManagerForm::~SentenceManagerForm()
{
    delete ui;
}

void SentenceManagerForm::on_pushButton_clicked()
{
    if(!db.isOpen())
        return;
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);

    QString strQuery = "SELECT * FROM sentenceRU";
    QSqlQuery* query = new QSqlQuery(strQuery,db);

    QList<QPair<int,QString>> lst;

    while(query->next())
    {
        lst.append(qMakePair(query->value("key").toInt(),query->value("sentence").toString()));
    }

    QSqlQuery* q = new QSqlQuery(db);
    for(int i = 0;i < lst.length();i++)
    {
        QTreeWidgetItem *itm_ = new QTreeWidgetItem();
        QString str = lst.at(i).second;
        itm_->setText(0, str);
        strQuery = "SELECT sentence FROM sentenceEN WHERE id = " + QString::number(lst.at(i).first);
        if(q->exec(strQuery))
        {
           for(int j = 0;q->next();j++)
           {
               QTreeWidgetItem* cItm = new QTreeWidgetItem();
               cItm->setText(j,q->value("sentence").toString());
               itm_->addChild(cItm);
           }
           ui->treeWidget->addTopLevelItem(itm_);
        }
    }

    //itm->setBackgroundColor(0, Qt::red);
    //itm->setTextColor(0, QColor(255,255,255,255));

/*
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, "Столбец №1");
    ui->treeWidget->addTopLevelItem(itm);

    QTreeWidgetItem *child = new QTreeWidgetItem();
    child->setText(0,"text");
    itm->addChild(child);
    //*/

}
