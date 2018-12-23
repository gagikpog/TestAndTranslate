#include "constructorform.h"
#include "ui_constructorform.h"
#include "word.h"

ConstructorForm::ConstructorForm(QWidget *parent) :QDialog(parent), ui(new Ui::ConstructorForm)
{
    ui->setupUi(this);
}

ConstructorForm::~ConstructorForm()
{
    delete ui;
}

void ConstructorForm::on_pushButton_clicked()
{
    Word* word = new Word(ui->frame);
    //word->setGeometry(0,0,word->size().width(),word->size().height());
    word->setGeometry(0,0,500,500);
    word->show();

}

