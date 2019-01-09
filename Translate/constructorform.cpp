#include "constructorform.h"
#include "ui_constructorform.h"
#include "settingsform.h"
#include "mainwindow.h"

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
    srand(time(NULL));
    //подключается к БД
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setPassword("sqlite18");
    db.open();
    //читает из БД все русские предложения
    readRUSentence();

    //создается таймер для отложенного вывода первого теста
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(MainWindow::loadStyle(SettingsForm::StyleFilename));
}

ConstructorForm::~ConstructorForm()
{
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
        int dTemp = distance(wPtrB->pos(),words.at(i)->posEnd());
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
    }
}

void ConstructorForm::readRUSentence()
{
    if(db.isOpen())
    {
        sentence.clear();
        //запрос на выделение всего
        QSqlQuery query = QSqlQuery("SELECT * FROM sentenceRU",db);
        //получаю номера колонок
        int keyNo = query.record().indexOf("key");
        int sentenceNo = query.record().indexOf("sentence");
        //по очереди вывожу все
        while (query.next())
            sentence.append(qMakePair(query.value(keyNo).toInt(),query.value(sentenceNo).toString()));
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

void ConstructorForm::loadSentence(int n)
{
    //если не существует такого предложения то выход
    if(n < 0 || n >= sentence.length())
        return;
    //получаем предложение
    QStringList strs = getTranslatesById(sentence.at(n).first);
    //если не удалось получить выходим
    if(strs.isEmpty())
        return;
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
        addWord(s.remove(QRegExp("[^\\w\']+")));
    }
}

QStringList ConstructorForm::getTranslatesById(int id)
{
    QStringList res;
    if(db.isOpen())
    {
        //запрос на выделение всего
        QSqlQuery query = QSqlQuery("SELECT * FROM sentenceEN WHERE id = " + QString::number(id)+";",db);
        //получаю номера колонок
        int sentenceNo = query.record().indexOf("sentence");
        //по очереди вывожу все
        while (query.next())
            res.append(query.value(sentenceNo).toString());
    }
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
    ui->labelStatus->setText(QString::number(right)+" | "+QString::number(wrong));
}

void ConstructorForm::updateTime()
{
    //остановить таймер
    tmr->stop();
    //загрузить первое предложение
    loadSentence(sentenceNum);
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
        str = str.remove(QRegExp("[^\\w\']+")).toLower();
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
    showStatus();
    msg.exec();
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
        //write mwssage
        //close();
    }
    //вывести следующее предложение
    loadSentence(sentenceNum);
}
