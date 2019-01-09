#ifndef CONSTRUCTORFORM_H
#define CONSTRUCTORFORM_H

#include <QDialog>
#include <QList>
#include <QSqlDatabase>
#include <QPair>
#include <QTimer>
#include <QTime>
#include <QtMath>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
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
    void ListConnect(int id);
    void setInterfaceLanguage(QString lang = "ru");

private slots:
    void updateTime();
    void on_btnTest_clicked();
    void on_btnSkip_clicked();

private:
    Ui::ConstructorForm *ui;
    QList<Word*> words;
    int connectionDistance = 50;
    int sentenceNum = 0;
    void readRUSentence();
    QList<QPair<int,QString>> sentence;
    QSqlDatabase db;
    void addWord(QString text);
    void loadSentence(int n);
    QStringList getTranslatesById(int id);
    QString getResultSentence();
    void showStatus();
    QTimer *tmr;
    int wrong = 0, right = 0;
    //Strings
    QString strGab = "Make a sentence!";
    QString strWrong = "Incorrectly written sentence!";
};

#endif // CONSTRUCTORFORM_H
