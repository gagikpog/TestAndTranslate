#include "constructorform.h"
#include "ui_constructorform.h"
#include <QtMath>

int distance(const QPoint& a,const QPoint& b)
{
    int w = a.x()-b.x();
    int h = a.y()-b.y();
    return qSqrt(w*w + h*h);
}


ConstructorForm::ConstructorForm(QWidget *parent) :QDialog(parent), ui(new Ui::ConstructorForm)
{
    ui->setupUi(this);
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

void ConstructorForm::on_pushButton_clicked()
{
    Word* word = new Word(ui->frame);
    words.append(word);
    //word->setGeometry(0,0,word->size().width(),word->size().height());

    word->setGeometry(0,0,100,40);
    word->setText("Hello");
    word->show();

}


