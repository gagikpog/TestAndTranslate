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

private:
    bool eventFilter(QObject *watched, QEvent *event);
    Ui::SentenceManagerForm *ui;
    QSqlDatabase db;
    //str
    QString strRemove = "&Remove";
    QString strAdd = "&Add";
    QString strEdit = "&Edit";
    QString strOk = "&OK";
    QString strReload = "Re&load";
    QString msgDelete = "Do you want to delete this offer?";
};

#endif // SENTENCEMANAGERFORM_H
