#ifndef CERTIFICATEFORM_H
#define CERTIFICATEFORM_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "loggingcategories.h"
#include "settingsform.h"
#include <QStandardPaths>
#include <QPrinter>

namespace Ui {
class CertificateForm;
}

class CertificateForm : public QDialog
{
    Q_OBJECT

public:
    explicit CertificateForm(QWidget *parent = 0);
    ~CertificateForm();
    void loadCertificate(QString jsonData);
    void setInterfaceLanguage(QString lang = "ru");
private slots:
    void on_btmSave_clicked();

private:
    Ui::CertificateForm *ui;
    QString strSave = "Save";
};

#endif // CERTIFICATEFORM_H
