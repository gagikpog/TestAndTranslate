#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();
    void setInterfaceLanguage(QString lang = "ru");
    static QString StyleFilename;
    static void readSettings();
private slots:
    void on_btmStyle_clicked();
    void on_rBtmCustom_clicked(bool checked);
    void on_rBtmLight_clicked(bool checked);
    void on_rBtmDark_clicked(bool checked);

private:
    Ui::SettingsForm *ui;
    void writeSettings();
    void readLocakSettings();
    static const QString settingsFilename;
};

#endif // SETTINGSFORM_H
