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
    static QString DatabaseName;
    static QString ApplicationLanguage;
    static int WordsCount;
    static QString testCheckMode;
    static void readSettings();
    static void writeLanguage();
    static QString getStyles();
    /**
     * flags - s | d | h
     * s - show. Открыть окно для обновления
     * d - download. Скачать без разрешения (использовать только с h)
     * h - hide. Открыть скрыто (если нет ключа d, то выводит актуальную версию программы)
     */
    static QString checkUpdate(QString flags = "s");
private slots:
    void on_btmStyle_clicked();
    void on_rBtmCustom_clicked(bool checked);
    void on_rBtmLight_clicked(bool checked);
    void on_rBtmDark_clicked(bool checked);
    void on_rBtmDefoult_clicked(bool checked);
    void on_btmSManager_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_spinBox_editingFinished();
    void on_testCheckModeBox_clicked(bool checked);
    void on_btnUpdate_clicked();

    void on_btnFeedback_clicked();

private:
    Ui::SettingsForm *ui;
    void writeSettings();
    void readLocakSettings();
    void selectRadioBatton(QString check);
    static QString loadStyle(QString filename);
    QString selectedRadioBtm = "Styles/defoult";
    QString customStyleFile = "";    
    QString msgBoxTitle = "Error";
    QString msgBoxWarning = "Login required";
    static QString StylesStr;
    static QString StyleFilename;
    static const QString settingsFilename;
    static QFont font;

};

#endif // SETTINGSFORM_H
