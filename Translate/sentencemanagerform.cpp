#include "sentencemanagerform.h"
#include "ui_sentencemanagerform.h"
#include "settingsform.h"
#include "mainwindow.h"
#include "readerform.h"

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

    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(MainWindow::loadStyle(SettingsForm::StyleFilename));
    ui->treeWidget->viewport()->installEventFilter(this);
}

SentenceManagerForm::~SentenceManagerForm()
{
    delete ui;
}

void SentenceManagerForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        strAdd = "&Добавить";
        strRemove = "&Удалить";
        strOk = "&ОК";
        strEdit = "&Редактировать";

        ui->btmAdd->setText(strAdd);
        ui->btmRemove->setText(strRemove);
        ui->btmOk->setText(strOk);
        ui->btmChange->setText(strEdit);
    }
}

void SentenceManagerForm::readSentence()
{
    if(!db.isOpen())
        return;
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(3);
    ui->treeWidget->hideColumn(1);
    ui->treeWidget->hideColumn(2);

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
        itm_->setText(0, lst.at(i).second);
        itm_->setText(1,QString::number(lst.at(i).first));
        strQuery = "SELECT sentence, key FROM sentenceEN WHERE id = " + QString::number(lst.at(i).first);
        if(q->exec(strQuery))
        {
           for(int j = 0;q->next();j++)
           {
               QTreeWidgetItem* cItm = new QTreeWidgetItem();
               cItm->setText(0, q->value("sentence").toString());
               cItm->setText(1, q->value("key").toString());
               cItm->setText(2, QString::number(lst.at(i).first));
               itm_->addChild(cItm);
           }
           ui->treeWidget->addTopLevelItem(itm_);
        }
    }
}

void SentenceManagerForm::prepareMenu(const QPoint &pos)
{
    QTreeWidget *tree = ui->treeWidget;

    selectionItem = tree->itemAt( pos );

    QAction *rmAct = new QAction(strRemove, this);
    QAction *addAct = new QAction(strAdd, this);
    QAction *editAct = new QAction(strEdit, this);

    connect(rmAct, SIGNAL(triggered()), this, SLOT(treeRemove()));
    connect(addAct, SIGNAL(triggered()), this, SLOT(treeAdd()));
    connect(editAct, SIGNAL(triggered()), this, SLOT(treeChange()));

    QMenu menu(this);
    menu.addAction(addAct);
    if(selectionItem)
    {
        menu.addAction(rmAct);
        menu.addAction(editAct);
    }
    menu.exec( tree->mapToGlobal(pos) );
}

void SentenceManagerForm::treeRemove()
{
    if(ui->treeWidget->selectedItems().isEmpty())
        return;
    QMessageBox* msg = new QMessageBox(this);
    msg->setStandardButtons(QMessageBox::Yes|QMessageBox::No);

    if(SettingsForm::ApplicationLanguage == "ru")
    {
        msg->setButtonText(QMessageBox::Yes,"&Да");
        msg->setButtonText(QMessageBox::No,"&Нет");
    }
    msg->setText("Are you remover this sentence?\n"+ui->treeWidget->currentItem()->text(0));
    if(msg->exec() == QMessageBox::Yes)
    {
        QTreeWidgetItem* itm = ui->treeWidget->currentItem();
        int key = itm->text(1).toInt();
        QSqlQuery* query = new  QSqlQuery(db);
        int err = 0;
        if(itm->text(2) == "")
        {
            QString strQuery = "DELETE FROM sentenceEN WHERE id = " + QString::number(key);
            if(!query->exec(strQuery))
                err++;
            strQuery = "DELETE FROM sentenceRU WHERE key = " + QString::number(key);
            if(!query->exec(strQuery))
                err++;
        }else {
            QString strQuery = "DELETE FROM sentenceEN WHERE key = " + QString::number(key);
            if(!query->exec(strQuery))
                err++;
        }
        if(err == 0)
            delete itm;
    }
}

void SentenceManagerForm::treeChange()
{
    if(ui->treeWidget->selectedItems().isEmpty())
        return;
    QTreeWidgetItem * itm = ui->treeWidget->currentItem();
    ReaderForm* form = new ReaderForm(this);
    form->setText(itm->text(0));
    form->exec();
    if(form->isChanged())
    {
        QSqlQuery* query = new QSqlQuery(db);
        QString strQuery = "UPDATE ";
        if(itm->text(2) == "")
        {
            strQuery += "sentenceRU SET sentence = \"" + form->Text() + "\" WHERE key = " + itm->text(1);
        } else {
            strQuery += "sentenceEN SET sentence = \"" + form->Text() + "\" WHERE key = " + itm->text(1);
        }
        if(query->exec(strQuery))
            itm->setText(0,form->Text());
    }
}

void SentenceManagerForm::treeAdd()
{
    ReaderForm* form = new ReaderForm(this);
    form->exec();
    if(form->isChanged())
    {
        form->Text();
        if(ui->treeWidget->selectedItems().isEmpty())
        {

        }else{
            QTreeWidgetItem* itm = ui->treeWidget->currentItem();
        }
    }
}

void SentenceManagerForm::on_btmOk_clicked()
{
    close();
}

bool SentenceManagerForm::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->treeWidget->viewport() && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *me = static_cast <QMouseEvent *> (event);

        QModelIndex index = ui->treeWidget->indexAt(me->pos());

        if (!index.isValid()) {
            ui->treeWidget->clearSelection();
        }
        return true;
    }
    return QDialog::eventFilter(watched, event);
}
