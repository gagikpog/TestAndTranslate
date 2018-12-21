#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QList>

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
    void setInterfaceLanguage();
    int listLineCount = 20;
private slots:
    void on_btmCheck_clicked();

private:
    Ui::TrainingForm *ui;
    void fillDB();
    void readAllData();
    void fillLisrs();
    bool testing();
    void changeReatingBD(QString enWord,int val);
    QList<ssint> data;
    QSqlDatabase db;
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
