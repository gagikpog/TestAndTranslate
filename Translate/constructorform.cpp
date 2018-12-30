#include "constructorform.h"
#include "ui_constructorform.h"
#include <QtMath>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

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
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setPassword("sqlite18");
    db.open();
    readRUSentence();

    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
}

ConstructorForm::~ConstructorForm()
{
    delete ui;
}

void ConstructorForm::ListUpdate(int id)
{
    Word* w = NULL;
    for(int i = 0;i<words.length();i++)
    {
        words.at(i)->repaint();
        if(words.at(i)->ID() == id)
            w = words.at(i);
    }
    if(w)
        w->repaint();
}

void ConstructorForm::ListConnect(int id)
{
    Word* wPtrB = NULL;
    Word* wPtrE = NULL;

    for(int i = 0;i < words.length();i++)
    {
        if(words.at(i)->ID() == id)
            wPtrB = words[i];
    }
    if(!wPtrB)
        return;
    int dMin = connectionDistance;

    for(int i = 0;i < words.length();i++)
    {
        if(words.at(i)->ID() == id)
            continue;
        int dTemp = distance(wPtrB->pos(),words.at(i)->posEnd());
        if (dTemp < dMin)
        {
            dMin = dTemp;
            wPtrE = words[i];
        }
    }
    if (dMin< connectionDistance && wPtrE)
    {
        wPtrE->setBack(wPtrB);
    }
}

void ConstructorForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->btnSkip->setText("Пропустить");
        ui->btnTest->setText("Проверка");
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
    Word* word = new Word(ui->frame);
    words.append(word);
    word->randomPos();
    word->setText(txt);
    word->show();
}

void ConstructorForm::loadSentence(int n)
{
    if(n < 0 || n >= sentence.length())
        return;
    QStringList strs = getTranslatesById(sentence.at(n).first);
    if(strs.isEmpty())
        return;
    for(int i = 0; i<words.length();i++)
        delete words[i];
    words.clear();

    QString txt = sentence[n].second;
    ui->frame->setTitle(txt);

    QString str = strs[0];
    str = str.toLower();
    QRegExp tagExp(" ");
    QStringList lst = str.split(tagExp);
    for(int i = 0; i < lst.length();i++)
    {
        QString s = lst[i];
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
    QString res = "";
    int start = 0;
    int count = 0;
    for(int i = 0;i < words.length();i++)
    {
        if(!words.at(i)->Prev())
        {
            count++;
            if(count >= 2)
                break;
            start = i;
        }
    }
    if(count == 1)
    {
        for(const Word*ptr = words.at(start);ptr;ptr = ptr->Next())
        {
            res += ptr->text();
        }
    }
    return res;
}

void ConstructorForm::showStatus()
{
    ui->labelStatus->setText(QString::number(right)+" | "+QString::number(wrong));
}

void ConstructorForm::updateTime()
{
    tmr->stop();
    loadSentence(sentenceNum);
}

void ConstructorForm::on_btnTest_clicked()
{
    QString res = getResultSentence();
    QMessageBox msg(QMessageBox::NoIcon,"","",QMessageBox::Ok,this,
        Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint) & ~Qt::WindowCloseButtonHint);
    msg.setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    if(res == "")
    {
        msg.setText(strGab);
        msg.exec();
        return;
    }

    QStringList lst = getTranslatesById(sentence.at(sentenceNum).first);
    for(int i = 0; i < lst.length();i++)
    {
        QString str = lst.at(i);
        str = str.remove(QRegExp("[^\\w\']+")).toLower();
        if(str == res)
        {
            msg.setText(sentence.at(sentenceNum).second+"\n\n"+lst.at(i));
            msg.setFont(QFont(font().family(),15));
            msg.exec();
            right++;
            on_btnSkip_clicked();
            showStatus();
            return;
        }
    }
    msg.setText(strWrong);
    wrong++;
    msg.exec();
    showStatus();
}

void ConstructorForm::on_btnSkip_clicked()
{
    sentenceNum++;
    if(sentenceNum >= sentence.length())
    {
        sentenceNum = 0;
        //end Testing
        //write mwssage
        //close();
    }
    loadSentence(sentenceNum);
}
