#include "constructorform.h"
#include "ui_constructorform.h"

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

void ConstructorForm::on_pushButton_clicked()
{
    Word* word = new Word(ui->frame);
    words.append(word);
    //word->setGeometry(0,0,word->size().width(),word->size().height());

    word->setGeometry(0,0,100,40);
    word->setText("Hello");
    word->show();

}


