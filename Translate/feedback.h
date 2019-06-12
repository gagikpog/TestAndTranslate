#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QBitArray>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class Feedback;
}

class Feedback : public QDialog
{
    Q_OBJECT

public:
    explicit Feedback(QWidget *parent = 0);
    ~Feedback();
    void setInterfaceLanguage(QString lang);

private slots:
    void on_textEdit_textChanged();
    void on_btnSend_clicked();
    void replyFinished(QNetworkReply* reply);

private:
    Ui::Feedback *ui;
    QString msgBoxTitle = "Error";
    QString msgBoxWarning = "Error when sending feedback";
};

#endif // FEEDBACK_H
