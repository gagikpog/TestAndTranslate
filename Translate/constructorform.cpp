#include "constructorform.h"
#include "ui_constructorform.h"

ConstructorForm::ConstructorForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConstructorForm)
{
    ui->setupUi(this);
}

ConstructorForm::~ConstructorForm()
{
    delete ui;
}
