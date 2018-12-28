#ifndef CONSTRUCTORFORM_H
#define CONSTRUCTORFORM_H

#include <QDialog>
#include <QList>
#include "word.h"
#include <QSqlDatabase>
#include <QPair>

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
    void ListConnect(int id);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ConstructorForm *ui;
    QList<Word*> words;
    int connectionDistance = 50;
    void readRUSentence();
    QList<QPair<int,QString>> sentence;
    QSqlDatabase db;
    void addWord(QString text);
    void loadSentence(int n);
    QStringList getTranslatesById(int id);
};

#endif // CONSTRUCTORFORM_H
