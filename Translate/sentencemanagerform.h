#ifndef SENTENCEMANAGER_H
#define SENTENCEMANAGER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPair>
#include <QList>

namespace Ui {
class SentenceManager;
}

class SentenceManagerForm : public QDialog
{
    Q_OBJECT

public:
    explicit SentenceManagerForm(QWidget *parent = 0);
    ~SentenceManagerForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SentenceManager *ui;
    QSqlDatabase db;
};

#endif // SENTENCEMANAGER_H
