#include "readerform.h"
#include "ui_readerform.h"

ReaderForm::ReaderForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReaderForm)
{
    ui->setupUi(this);
}

void ReaderForm::setText(QString txt)
{
    ui->textEdit->setText(txt);
}

bool ReaderForm::isChanged() const
{
    return changed;
}

QString ReaderForm::Text() const
{
    QString txt = ui->textEdit->toPlainText();
    txt = txt.simplified();
    return txt;
}

ReaderForm::~ReaderForm()
{
    delete ui;
}

void ReaderForm::on_btmOk_clicked()
{
    changed = true;
    close();
}
