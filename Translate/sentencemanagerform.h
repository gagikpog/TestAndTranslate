#ifndef SENTENCEMANAGERFORM_H
#define SENTENCEMANAGERFORM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPair>
#include <QList>
#include <QMenu>
#include <QMessageBox>
#include <QTreeWidget>
#include <QDebug>

namespace Ui {
class SentenceManagerForm;
}

class SentenceManagerForm : public QDialog
{
    Q_OBJECT

public:
    explicit SentenceManagerForm(QWidget *parent = 0);
    ~SentenceManagerForm();
    void setInterfaceLanguage(QString lang);
private slots:
    void readSentence();
    void prepareMenu(const QPoint & pos );
    void treeRemove();
    void treeChange();
    void treeAdd();
    void treeAddItem();
    void on_btmOk_clicked();

private:
    Ui::SentenceManagerForm *ui;
    QSqlDatabase db;
    QTreeWidgetItem* selectionItem;
    //str
    QString strRemove = "&Remove";
    QString strAdd = "&Add";
    QString strEdit = "&Edit";
    QString strOk = "&OK";
};

#endif // SENTENCEMANAGERFORM_H
