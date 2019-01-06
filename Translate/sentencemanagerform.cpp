#include "sentencemanagerform.h"
#include "ui_sentencemanagerform.h"

SentenceManagerForm::SentenceManagerForm(QWidget *parent) : QDialog(parent), ui(new Ui::SentenceManagerForm)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setPassword("sqlite18");
    db.open();

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(prepareMenu(QPoint)));
    readSentence();
    //btm connect
    connect(ui->btmAdd,SIGNAL(clicked()),this,SLOT(treeAdd()));
    connect(ui->btmChange,SIGNAL(clicked()),this,SLOT(treeChange()));
    connect(ui->btmRemove,SIGNAL(clicked()),this,SLOT(treeRemove()));
}

SentenceManagerForm::~SentenceManagerForm()
{
    delete ui;
}

void SentenceManagerForm::readSentence()
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

void SentenceManagerForm::prepareMenu(const QPoint &pos)
{
    QTreeWidget *tree = ui->treeWidget;

    selectionItem = tree->itemAt( pos );

    QAction *rmAct = new QAction(tr("Remove"), this);
    QAction *addAct = new QAction(tr("Add"), this);
    QAction *chAct = new QAction(tr("Change"), this);

    connect(rmAct, SIGNAL(triggered()), this, SLOT(treeRemove()));
    connect(addAct, SIGNAL(triggered()), this, SLOT(treeAdd()));
    connect(chAct, SIGNAL(triggered()), this, SLOT(treeChange()));

    QMenu menu(this);
    menu.addAction(addAct);
    if(selectionItem)
    {
        menu.addAction(rmAct);
        menu.addAction(chAct);
    }
    menu.exec( tree->mapToGlobal(pos) );
}

void SentenceManagerForm::treeRemove()
{
    QMessageBox::information(this,"","treeRemove");
}

void SentenceManagerForm::treeChange()
{
    QMessageBox::information(this,"","treeChange");
}

void SentenceManagerForm::treeAdd()
{
    QMessageBox::information(this,"","treeAdd");

}

void SentenceManagerForm::treeAddItem()
{
    QMessageBox::information(this,"","treeAddItem");
}

void SentenceManagerForm::on_btmOk_clicked()
{
    close();
}
