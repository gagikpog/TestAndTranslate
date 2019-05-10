#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QList>
#include <QModelIndex>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDate>

namespace Ui {
class TrainingForm;
}

struct ssint;

class TrainingForm : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingForm(QWidget *parent = 0);
    ~TrainingForm();
    void setInterfaceLanguage(QString lang = "ru");
    QStringList result();
private slots:
    void on_btmCheck_clicked();
    void on_btmNext_clicked();
    void on_list1_clicked(const QModelIndex &index);
    void on_list2_clicked(const QModelIndex &index);

private:
    Ui::TrainingForm *ui;
    void fillDB();
    void readAllData();
    void fillLisrs();
    bool testing();
    void changeReatingBD(QString enWord,int val);
    QList<ssint> data;
    QSqlDatabase db;
    int ansRight = 0, ansWrong = 0;
    int listLineCount = 5;
};

struct ssint
{
    ssint(){}
    ssint(QString _en,QString _ru,int _reating):en(_en),ru(_ru),rating(_reating){}
    QString en;
    QString ru;
    int rating;
    bool checked = false;
};

#endif // TRAININGFORM_H
