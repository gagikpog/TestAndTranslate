#include "sentencemanagerform.h"
#include "ui_sentencemanagerform.h"
#include "settingsform.h"
#include "mainwindow.h"
#include "readerform.h"
#include "loggingcategories.h"
#include "header.h"

SentenceManagerForm::SentenceManagerForm(QWidget *parent) : QDialog(parent), ui(new Ui::SentenceManagerForm)
{
    ui->setupUi(this);
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
        qDebug(logDebug())<<"SentenceManagerForm: DB open error>";
        qDebug(logDebug())<<"\t\t"<<db.lastError().text();
    }else qDebug(logDebug())<<"SentenceManagerForm: DB opened";
    //задать заголовок окна
    setWindowTitle("Task Editor");
    //Это свойство содержит информацию о том, как виджет отображает контекстное меню.
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //привязать процедуру на нажатие правой кнопки
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(prepareMenu(QPoint)));
    //загрузить из БД все предложения
    readSentence();
    //привязать события на кнопки управления
    connect(ui->btmAdd,SIGNAL(clicked()),this,SLOT(treeAdd()));
    connect(ui->btmChange,SIGNAL(clicked()),this,SLOT(treeChange()));
    connect(ui->btmRemove,SIGNAL(clicked()),this,SLOT(treeRemove()));
    connect(ui->btmReload,SIGNAL(clicked()),this,SLOT(readSentence()));
    //задать язык интерфейса
    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    //установить CSS стили для окна
    setStyleSheet(SettingsForm::getStyles());
    //перенаправить в класс SentenceManagerForm все события
    ui->treeWidget->viewport()->installEventFilter(this);
}

SentenceManagerForm::~SentenceManagerForm()
{
    //закрываю соединение
    db.close();
    db.removeDatabase("data.db");
    delete ui;
}

void SentenceManagerForm::setInterfaceLanguage(QString lang)
{
    //меняет язык интерфейса
    if(lang == "ru")
    {
        strAdd = "&Добавить";
        strRemove = "&Удалить";
        strOk = "&ОК";
        strEdit = "&Редактировать";
        strReload = "&Обновить";
        msgDelete = "Вы хотите удалить это предложение?";
        setWindowTitle("Редактор заданий");

        ui->btmAdd->setText(strAdd);
        ui->btmRemove->setText(strRemove);
        ui->btmOk->setText(strOk);
        ui->btmChange->setText(strEdit);
        ui->btmReload->setText(strReload);
    }
}

void SentenceManagerForm::readSentence()
{
#ifndef QODBC_DATABASE
    //проверка, открыта ли база
    if(!db.isOpen())
    {
        qDebug(logDebug())<<"SentenceManagerForm: DB not opened";
        return;
    }
#endif
    //удалить содержимое виджета
    ui->treeWidget->clear();
    //количество колонок три
    ui->treeWidget->setColumnCount(3);
    //скрыть второй и третий
    ui->treeWidget->hideColumn(1);
    ui->treeWidget->hideColumn(2);
    //запрос на выделение всех предложений
    QString strQuery = "SELECT * FROM sentenceRU";
    //объект запросов
    QSqlQuery* query = new QSqlQuery(strQuery,db);
    //суда загрузится предложения
    QList<QPair<int,QString>> lst;

    while(query->next())
    {
        //загрузка предложений
        lst.append(qMakePair(query->value("key").toInt(),query->value("sentence").toString()));
    }
    if(lst.isEmpty())
    {
        qDebug(logDebug())<<"SentenceManagerForm: query result is empty";
    }
    //объект запросов для английских предложений
    QSqlQuery* q = new QSqlQuery(db);
    for(int i = 0;i < lst.length();i++)
    {
        //корневая строка (русская)
        QTreeWidgetItem *itm = new QTreeWidgetItem();
        //задать текст
        itm->setText(0, lst.at(i).second);
        itm->setText(1,QString::number(lst.at(i).first));
        //запрос на выделение английских предложений
        strQuery = "SELECT sentence, key FROM sentenceEN WHERE id = " + QString::number(lst.at(i).first);
        if(q->exec(strQuery))
        {
           for(int j = 0;q->next();j++)
           {
               //дочерняя строка (английская)
               QTreeWidgetItem* cItm = new QTreeWidgetItem();
               //задать текст
               cItm->setText(0, q->value("sentence").toString());
               cItm->setText(1, q->value("key").toString());
               cItm->setText(2, QString::number(lst.at(i).first));
               //добавить родителя
               itm->addChild(cItm);
           }
           //добавить на виджет
           ui->treeWidget->addTopLevelItem(itm);
        }else {
            qDebug(logDebug())<<"SentenceManagerForm: query result is empty";
        }
    }
}

void SentenceManagerForm::prepareMenu(const QPoint &pos)
{
    //поля в контекстом меню
    QAction *rmAct = new QAction(strRemove, this);
    QAction *addAct = new QAction(strAdd, this);
    QAction *editAct = new QAction(strEdit, this);
    QAction *reloadAct = new QAction(strReload, this);
    //привязка события на нажатие с процедурами
    connect(rmAct, SIGNAL(triggered()), this, SLOT(treeRemove()));
    connect(addAct, SIGNAL(triggered()), this, SLOT(treeAdd()));
    connect(editAct, SIGNAL(triggered()), this, SLOT(treeChange()));
    connect(reloadAct, SIGNAL(triggered()), this, SLOT(readSentence()));
    //создания меню
    QMenu menu(this);
    //добавления пунктов
    menu.addAction(addAct);
    //если ничего не выбрано то не нужно добавлять пункты “редактирование” и “удаление”
    if(ui->treeWidget->itemAt( pos ))
    {
        menu.addAction(editAct);
        menu.addAction(rmAct);
    }
    menu.addAction(reloadAct);
    //вызвать меню
    menu.exec( ui->treeWidget->mapToGlobal(pos) );
}

void SentenceManagerForm::treeRemove()
{
    //если ничего не выбрано то выйти
    if(ui->treeWidget->selectedItems().isEmpty())
        return;
    QMessageBox* msg = new QMessageBox(this);
    //задать кнопки для MessageBox
    msg->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    //если язык приложения русский поменять название кнопок
    if(SettingsForm::ApplicationLanguage == "ru")
    {
        msg->setButtonText(QMessageBox::Yes,"&Да");
        msg->setButtonText(QMessageBox::No,"&Нет");
    }
    //задать текст сообщения
    msg->setText(msgDelete + "\n"+ui->treeWidget->currentItem()->text(0));
    //если нажали кнопку “Да”
    if(msg->exec() == QMessageBox::Yes)
    {
        //получаем выделенную строку
        QTreeWidgetItem* itm = ui->treeWidget->currentItem();
        //получаем код записи
        int key = itm->text(1).toInt();
        QSqlQuery* query = new  QSqlQuery(db);
        //счетчик для определения ошибки
        int err = 0;
        //если текст корневой (русский) то нужно удалить и дочерние(английские) записи
        if(itm->text(2) == "")
        {
            QString strQuery = "DELETE FROM sentenceEN WHERE id = " + QString::number(key);
            if(!query->exec(strQuery))
                err++;
            strQuery = "DELETE FROM sentenceRU WHERE key = " + QString::number(key);
            if(!query->exec(strQuery))
                err++;
        }else {
            //иначе только саму строку
            QString strQuery = "DELETE FROM sentenceEN WHERE key = " + QString::number(key);
            if(!query->exec(strQuery))
                err++;
        }
        //если в БД все успешно удалено то удаляем запись из дерева
        if(err == 0)
            delete itm;
        else qDebug(logDebug())<<"SentenceManagerForm: failed to delete the sentence";

    }
}

void SentenceManagerForm::treeChange()
{
    //если ничего не выбрано то выйти
    if(ui->treeWidget->selectedItems().isEmpty())
        return;
    //получаем выделенную строку
    QTreeWidgetItem * itm = ui->treeWidget->currentItem();
    //создаем форму для ввода
    ReaderForm* form = new ReaderForm(this);
    //задаем текст для редактирования
    form->setText(itm->text(0));
    //вызываем форму
    form->exec();
    //если была нажата сохранить
    if(form->isChanged())
    {
        //запрос на изменение
        QSqlQuery* query = new QSqlQuery(db);
        QString strQuery = "UPDATE ";
        if(itm->text(2) == "")
        {
            strQuery += "sentenceRU SET sentence = \"" + form->Text() + "\" WHERE key = " + itm->text(1);
        } else {
            strQuery += "sentenceEN SET sentence = \"" + form->Text() + "\" WHERE key = " + itm->text(1);
        }
        //если в БД удачно изменено то меняем в дереве
        if(query->exec(strQuery))
            itm->setText(0,form->Text());
        else qDebug(logDebug())<<"SentenceManagerForm: failed to change the sentence";
    }
}

void SentenceManagerForm::treeAdd()
{
    //создаем форму для ввода
    ReaderForm* form = new ReaderForm(this);
    //вызываем форму
    form->exec();
    //если была нажата сохранить
    if(form->isChanged())
    {
        //создание объекта запросов
        QSqlQuery* query = new QSqlQuery(db);
        QString strQuery = "INSERT INTO ";
        //если что то не выбрано
        if(ui->treeWidget->selectedItems().isEmpty())
        {
            //запрос на добавление
            strQuery += "sentenceRU (sentence) VALUES (\"" + form->Text() + "\");";
            //если в БД удачно добавлена запись
            if(query->exec(strQuery))
            {
                //запрос, чтобы получить код записи
                strQuery = "SELECT key FROM sentenceRU WHERE sentence = \"" + form->Text() + "\";";
                if(query->exec(strQuery))
                {
                    if(query->next())
                    {
                        //получаем код и добавляем в дерево
                        QString key = query->value("key").toString();
                        QTreeWidgetItem* itm = new QTreeWidgetItem();
                        itm->setText(0,form->Text());
                        itm->setText(1,key);
                        ui->treeWidget->addTopLevelItem(itm);
                    }else {
                        qDebug(logDebug())<<"SentenceManagerForm: failed to add the sentence";
                    }
                }
            }
        }else{
            //иначе нужно добавить не в корень а в дочернюю часть
            //получаем выделенную строку
            QTreeWidgetItem* itm = ui->treeWidget->currentItem();
            //если оно является дочерной то нужно взять его родителя
            if(itm->text(2) != "")
            {
                itm = itm->parent();
            }
            //запрос на добавление
            strQuery += "sentenceEN (id,sentence) VALUES (" + itm->text(1) + ",\"" + form->Text() + "\");";
            if(query->exec(strQuery))
            {
                //запрос, чтобы получить код записи
                strQuery = "SELECT key FROM sentenceEN WHERE sentence = \"" + form->Text() + "\";";
                if(query->exec(strQuery))
                {
                    if(query->next())
                    {
                        //получаем код и добавляем к родителю
                        QString key = query->value("key").toString();
                        QTreeWidgetItem* cItm = new QTreeWidgetItem();
                        cItm->setText(0,form->Text());
                        cItm->setText(1,key);
                        cItm->setText(2,itm->text(1));
                        itm->addChild(cItm);
                    }else {
                        qDebug(logDebug())<<"SentenceManagerForm: failed to add the sentence";
                    }
                }
            }
        }
    }
}

bool SentenceManagerForm::eventFilter(QObject *watched, QEvent *event)
{
    //это процедура убирает выделения если мы нажимаем на пустую область на виджете
    //если виджет находится в области видимости и событие равно нажатие мыши
    if (watched == ui->treeWidget->viewport() && event->type() == QEvent::MouseButtonRelease) {
        //преобразуем event в mouseEvent
        QMouseEvent *me = static_cast <QMouseEvent *> (event);
        //по координату нажатия получаем индекс элемента на которую нажал
        QModelIndex index = ui->treeWidget->indexAt(me->pos());
        //если нет элемента с таким индексом то убираем выделение
        if (!index.isValid()) {
            ui->treeWidget->clearSelection();
        }
    }
    //передаем событие дальше к виджету
    return QDialog::eventFilter(watched, event);
}
