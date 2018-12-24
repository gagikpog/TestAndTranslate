#ifndef CONSTRUCTORFORM_H
#define CONSTRUCTORFORM_H

#include <QDialog>
#include <QList>
#include "word.h"

namespace Ui {
class ConstructorForm;
}

class ConstructorForm : public QDialog
{
    Q_OBJECT

public:
    explicit ConstructorForm(QWidget *parent = 0);
    ~ConstructorForm();
    void ListUpdate(int id);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConstructorForm *ui;
    QList<Word*> words;
};

#endif // CONSTRUCTORFORM_H
