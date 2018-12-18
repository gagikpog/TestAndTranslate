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
    void on_pushButton_clicked();
    void replyFinished(QNetworkReply* reply);
    void on_msgInput_returnPressed();

private:
    Ui::TranslateForm *ui;
};

#endif // TRANSLATEFORM_H
