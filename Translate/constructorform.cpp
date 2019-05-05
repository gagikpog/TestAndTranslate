#include "constructorform.h"
#include "ui_constructorform.h"
#include "settingsform.h"
#include "mainwindow.h"
#include "linefeed.h"
#include "loggingcategories.h"
#include "header.h"

//возвращает расстояние  между двумя точками
int distance(const QPoint& a,const QPoint& b)
{
    int w = a.x()-b.x();
    int h = a.y()-b.y();
    return qSqrt(w*w + h*h);
}

ConstructorForm::ConstructorForm(QWidget *parent) :QDialog(parent), ui(new Ui::ConstructorForm)
{
    ui->setupUi(this);
    setWindowTitle("Puzzle");
    srand(time(NULL));
    //подключается к БД
#ifndef QODBC_DATABASE
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
#else
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=data.mdb;");
#endif
    db.setPassword("sqlite18");
    if(!db.open()){
        qDebug(logDebug())<<"ConstructorForm:DB open error>";
        qDebug(logDebug())<<"\t\t"<<db.lastError().text();
    }else qDebug(logDebug())<<"ConstructorForm:DB opened";
    //читает из БД все русские предложения
    readRUSentence();

    //создается таймер для отложенного вывода первого теста
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(SettingsForm::getStyles());
    ui->btnLineFeed->setVisible(false);
    ui->btnSkip->setVisible(false);
    ui->btnSkip->setEnabled(false);
    ui->btnTest->setEnabled(false);
    showStatus();
}

ConstructorForm::~ConstructorForm()
{
    //закрываю соединение
    db.close();
    db.removeDatabase(db.databaseName());
    delete ui;
}

void ConstructorForm::ListUpdate(int id)
{
    //перерисовывает все объекты типа  word
    Word* focus = NULL;
    for(int i = 0;i<words.length();i++)
    {
        //перерисовка
        words.at(i)->repaint();
        //поиск объекта находящейся в фокусе
        if(words.at(i)->ID() == id)
            focus = words.at(i);
    }
    //перерисовка
    if(focus)
        focus->repaint();
}

void ConstructorForm::ListConnect(int id)
{
    //процедура для прикрепления объектов после отжатия мыши
    //создаем указатели для переднего и заднего объекта
    Word* wPtrB = NULL;
    Word* wPtrE = NULL;

    //находим задний объект (мы знаем его ID)
    for(int i = 0;i < words.length();i++)
    {
        if(words.at(i)->ID() == id)
        {
            wPtrB = words[i];
            break;
        }
    }
    //если не удалось найти выходим
    if(!wPtrB)
        return;

    int dMin = connectionDistance;

    //ищем минимальное расстояние
    for(int i = 0;i < words.length();i++)
    {
        //пропускаем себя
        if(words.at(i)->ID() == id)
            continue;
        //рассчитать расстояние
        int dTemp = distance(wPtrB->posBegin(),words.at(i)->posEnd());
        //если оно меньше минимального
        if (dTemp < dMin)
        {
            //он становится минимальным
            dMin = dTemp;
            //берется  указатель на него
            wPtrE = words[i];
        }
    }
    //если объект найден
    if (wPtrE)
    {
        //соединяем второй объект к первому
        wPtrE->setBack(wPtrB);
    }
}

void ConstructorForm::setInterfaceLanguage(QString lang)
{
    //установить русский язык
    if(lang == "ru")
    {
        ui->btnSkip->setText("П&ропустить");
        ui->btnTest->setText("&Проверка");
        strGab = "Составьте предложение!";
        strWrong = "Неверно составлено предложение!";
        strEnd = "Тестирование закончено, нажмите ОК чтобы посмотреть результат.";
        setWindowTitle("Пазл");
    }
}

void ConstructorForm::readRUSentence()
{
#ifndef QODBC_DATABASE
    if(!db.isOpen())
    {
        qDebug(logDebug())<<"ConstructorForm: DB not opened";
        return;
    }
#endif
    sentence.clear();
    //запрос на выделение всего
    QSqlQuery query = QSqlQuery("SELECT * FROM sentenceRU",db);
    //получаю номера колонок
    int keyNo = query.record().indexOf("key");
    int sentenceNo = query.record().indexOf("sentence");
    //по очереди вывожу все
    while (query.next())
        sentence.append(qMakePair(query.value(keyNo).toInt(),query.value(sentenceNo).toString()));
    if(sentence.isEmpty())
    {
        ui->btnSkip->setEnabled(false);
        ui->btnTest->setEnabled(false);
        qDebug(logDebug())<<"ConstructorForm: sentence is empty";
    }
}

void ConstructorForm::addWord(QString txt)
{
    //создать новый объект
    Word* word = new Word(ui->frame);
    //добавить в лист
    words.append(word);
    //задать позицию
    word->randomPos();
    //задать текст
    word->setText(txt);
    word->show();
}

bool ConstructorForm::loadSentence(int n)
{
    //если не существует такого предложения то выход
    if(n < 0 || n >= sentence.length())
        return false;
    //получаем предложение
    QStringList strs = getTranslatesById(sentence.at(n).first);
    //если не удалось получить выходим
    if(strs.isEmpty())
        return false;
    //удаляем все предыдущие слова из формы
    for(int i = 0; i<words.length();i++)
        delete words[i];
    words.clear();

    //выводим перевод предложение
    ui->frame->setTitle(sentence[n].second);

    //приводим к нижнему регистру
    QString str = strs[0];
    str = str.toLower();
    QRegExp tagExp(" ");
    //разделяем на слова
    QStringList lst = str.split(tagExp);
    //добавляем на форму
    for(int i = 0; i < lst.length();i++)
    {
        QString s = lst[i];
        //убираем символы и пробелы
        addWord(s.remove(QRegExp("[^\\w`]+")));
    }
    return true;
}

QStringList ConstructorForm::getTranslatesById(int id)
{
    QStringList res;

#ifndef QODBC_DATABASE
    if(!db.isOpen())
    {
        return res;
    }
#endif

    //запрос на выделение всего
    QSqlQuery query = QSqlQuery("SELECT * FROM sentenceEN WHERE id = " + QString::number(id)+";",db);
    //получаю номера колонок
    int sentenceNo = query.record().indexOf("sentence");
    //по очереди вывожу все
    while (query.next())
        res.append(query.value(sentenceNo).toString());

    return res;
}

QString ConstructorForm::getResultSentence()
{
    //себетает предложение составленный конструктором
    QString res = "";
    //позиция начало строки
    int start = 0;
    //количество начал строк (если объекты не все соединены между собой)
    int count = 0;
    //ищим начало строки
    for(int i = 0;i < words.length();i++)
    {
        //если спереди нет слово то это начало
        if(!words.at(i)->Prev())
        {
            //количество совпадений
            count++;
            //если уже дна или больше то выходим
            if(count >= 2)
                return res;
            //сохраняем номер начала строки
            start = i;
        }
    }
    //составить строку
    for(const Word*ptr = words.at(start);ptr;ptr = ptr->Next())
    {
        res += ptr->text();
    }
    return res;
}

void ConstructorForm::showStatus()
{
    //вывод количество правильных и неправильных ответов
    QString msg = "Test: ";
    if(SettingsForm::ApplicationLanguage == "ru")
        msg = "Тест: ";
    ui->labelStatus->setText(msg + QString::number(sentenceNum + 1)+" / "+QString::number(sentence.length()));
}

void ConstructorForm::updateTime()
{
    //остановить таймер
    tmr->stop();
    //загрузить первое предложение
    if(loadSentence(sentenceNum))
    {
        ui->btnSkip->setEnabled(true);
        ui->btnTest->setEnabled(true);
    }
}

void ConstructorForm::on_btnTest_clicked()
{
    //проверка результата
    QString res = getResultSentence();
    QMessageBox msg(QMessageBox::NoIcon,"","",QMessageBox::Ok,this,
        Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint) & ~Qt::WindowCloseButtonHint);
    msg.setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    //если предложение не составлено сообщить и выйти
    if(res == "")
    {
        msg.setText(strGab);
        msg.exec();
        return;
    }
    //получить все правильные ответы
    QStringList lst = getTranslatesById(sentence.at(sentenceNum).first);
    //сравнение строк
    for(int i = 0; i < lst.length();i++)
    {
        //берется строка и убираются все символы и пробелы а также приводится к нижнему регистру
        QString str = lst.at(i);
        str = str.remove(QRegExp("[^\\w`]+")).toLower();
        //если совпадение
        if(str == res)
        {
            //сообщаем
            msg.setText(sentence.at(sentenceNum).second+"\n\n"+lst.at(i));
            msg.setFont(QFont(font().family(),15));
            msg.exec();
            //увеличить количество правильных ответов
            right++;
            //загрузить следующее предложение
            on_btnSkip_clicked();
            //обновить результат
            showStatus();
            //выход
            return;
        }
    }
    //значит предложение составлено неверно
    //сообщить
    msg.setText(strWrong);
    //увеличить количество ошибок и обновить
    wrong++;
    msg.exec();
    //загрузить следующее предложение
    on_btnSkip_clicked();
    showStatus();
}

void ConstructorForm::on_btnSkip_clicked()
{
    //следующее предложение
    sentenceNum++;
    //предложение закончились
    if(sentenceNum >= sentence.length())
    {
        sentenceNum = 0;
        //end Testing
        QMessageBox msg(QMessageBox::NoIcon,"","",QMessageBox::Ok,this,
            Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint) & ~Qt::WindowCloseButtonHint);
        msg.setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
        //write mwssage
        msg.setText(strEnd);
        msg.exec();
        close();
    }
    //вывести следующее предложение
    loadSentence(sentenceNum);
}

void ConstructorForm::on_btnLineFeed_clicked()
{
    //создать новый объект
    LineFeed* feed = new LineFeed(ui->frame);
    //добавить в лист
    words.append(feed);
    //задать позицию
    //feed->setText("");
    feed->randomPos();
    feed->show();
}
