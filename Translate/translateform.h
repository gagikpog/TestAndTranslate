#ifndef TRANSLATEFORM_H
#define TRANSLATEFORM_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QMessageBox>
#include <QByteArray>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QKeyEvent>
#include <QDebug>
#include <QTableWidgetItem>

namespace Ui {
class TranslateForm;
}

class TranslateForm : public QDialog
{
    Q_OBJECT

public:
    explicit TranslateForm(QWidget *parent = 0);
    ~TranslateForm();
    void setInterfaceLanguage(QString lang = "ru");

private slots:
    void replyFinished(QNetworkReply* reply);
    void on_btmLanguage_clicked();
    void on_btmFavorite_clicked();
    void on_btmTranslate_clicked();
    void ReadDB();
    void on_msgInput_returnPressed();
    void on_btmRemove_clicked();
    void resizeEvent(QResizeEvent* event);
    void on_btmClear_clicked();
    void readTranslateFromFile();
    QString offlineTranslate(QString txt);
private:
    Ui::TranslateForm *ui;
    QString TranslateLanguage = "ru";
    QString msgBoxQuestion = "Do you really want to delete this word?";
    QString msgBoxWarning = "Please select a word to remove!";
    QString msgBoxTitle = "Message";
    QString msgBoxFavorite = "You need to fill in the fields before adding to favorites!";
    QSqlDatabase db;
};

#endif // TRANSLATEFORM_H
