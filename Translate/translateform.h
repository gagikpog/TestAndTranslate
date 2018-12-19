#ifndef TRANSLATEFORM_H
#define TRANSLATEFORM_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>

namespace Ui {
class TranslateForm;
}

class TranslateForm : public QDialog
{
    Q_OBJECT

public:
    explicit TranslateForm(QWidget *parent = 0);
    ~TranslateForm();

private slots:
    void replyFinished(QNetworkReply* reply);
    void on_btmLanguage_clicked();
    void on_btmFavorite_clicked();
    void on_btmTranslate_clicked();
    void ReadDB();

private:
    Ui::TranslateForm *ui;
    QString TranslateLanguage = "ru";
};

#endif // TRANSLATEFORM_H
