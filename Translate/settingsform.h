#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

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
    static QString ApplicationLanguage;
    static int WordsCount;
    static void readSettings();
    static void writeLanguage();
    static QString getStyles();
private slots:
    void on_btmStyle_clicked();
    void on_rBtmCustom_clicked(bool checked);
    void on_rBtmLight_clicked(bool checked);
    void on_rBtmDark_clicked(bool checked);
    void on_rBtmDefoult_clicked(bool checked);
    void on_btmSManager_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_spinBox_editingFinished();

private:
    Ui::SettingsForm *ui;
    void writeSettings();
    void readLocakSettings();
    void selectRadioBatton(QString check);
    static QString loadStyle(QString filename);
    QString selectedRadioBtm = "Styles/defoult";
    QString customStyleFile = "";    

    static QString StylesStr;
    static QString StyleFilename;
    static const QString settingsFilename;
    static QFont font;
};

#endif // SETTINGSFORM_H
