#include "settingsform.h"
#include "sentencemanagerform.h"
#include "ui_settingsform.h"
#include "mainwindow.h"

QString SettingsForm::StyleFilename = ":/Styles/dark.qss";
QString SettingsForm::ApplicationLanguage = "en";
int SettingsForm::WordsCount = 8;
QString SettingsForm::StylesStr = "";
const QString SettingsForm::settingsFilename = "settings.ini";

QFont SettingsForm::font;


SettingsForm::SettingsForm(QWidget *parent) :QDialog(parent), ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    setWindowTitle("Settings");
    readLocakSettings();
    setStyleSheet(getStyles());
    setInterfaceLanguage(ApplicationLanguage);
    ui->fontComboBox->setCurrentFont(font);
    ui->spinBox->setValue(WordsCount);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->rBtmDark->setText("Темный");
        ui->rBtmLight->setText("Светлая");
        ui->rBtmCustom->setText("Другой");
        ui->rBtmDefoult->setText("По умолчанию");
        ui->btmStyle->setText("Загрузить стиль");
        ui->labelWord->setText("Количество слов");
        setWindowTitle("Настройки");
    }
}

void SettingsForm::readSettings()
{
    QSettings settings(settingsFilename, QSettings::IniFormat);
    StyleFilename = settings.value("styleFile", "").toString();
    ApplicationLanguage = settings.value("language", "en").toString();
    font.setFamily(settings.value("font", "Ubuntu").toString());
    WordsCount = settings.value("wordsCount","8").toInt();

    StylesStr = loadStyle(StyleFilename);
}

void SettingsForm::writeLanguage()
{
    QSettings settings(settingsFilename, QSettings::IniFormat);
    settings.setValue("language", ApplicationLanguage);
}

QString SettingsForm::getStyles()
{
    return StylesStr + "QWidget{font-family: \"" + font.family() + "\";}";
}

void SettingsForm::on_btmStyle_clicked()
{
    QFileDialog* dlg = new QFileDialog(this);
    QString res = dlg->getOpenFileName(this,"caption","Styles","Qt style files(*.qss);; All files (*.*)");
    if(res != "")
    {
        StyleFilename = res;
        StylesStr = loadStyle(StyleFilename);
        setStyleSheet(getStyles());
        customStyleFile = res;
        writeSettings();
        selectedRadioBtm = "custom";
    }else {
        selectRadioBatton(selectedRadioBtm);
    }
}

void SettingsForm::writeSettings()
{
    QString check = "dark";
    if(ui->rBtmLight->isChecked())
        check = "light";
    if(ui->rBtmCustom->isChecked())
        check = "custom";
    if(ui->rBtmDefoult->isChecked())
        check = "defoult";

    QSettings settings(settingsFilename, QSettings::IniFormat);
    settings.setValue("styleFile", StyleFilename);
    settings.setValue("checkbux",check );
    settings.setValue("customStyleFile",customStyleFile);
    settings.setValue("font",font.family());
    settings.setValue("wordsCount",WordsCount);
}

void SettingsForm::readLocakSettings()
{
    QSettings settings(settingsFilename, QSettings::IniFormat);
    selectRadioBatton(settings.value("checkbux", "").toString());
    customStyleFile = settings.value("customStyleFile", "").toString();
}

void SettingsForm::selectRadioBatton(QString check)
{
    ui->rBtmDefoult->setChecked(check == "defoult");
    ui->rBtmCustom->setChecked(check == "custom");
    ui->rBtmDark->setChecked(check == "dark");
    ui->rBtmLight->setChecked(check == "light");
    ui->btmStyle->setEnabled(check == "custom");
    selectedRadioBtm = check;
}

void SettingsForm::on_rBtmCustom_clicked(bool checked)
{
    ui->btmStyle->setEnabled(checked);
    if(!QFile::exists(customStyleFile)){
        on_btmStyle_clicked();
    }else{
        StyleFilename = customStyleFile;
        StylesStr = loadStyle(StyleFilename);
        setStyleSheet(getStyles());
        writeSettings();
    }
}

void SettingsForm::on_rBtmLight_clicked(bool )
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = ":/Styles/light.qss";
    StylesStr = loadStyle(StyleFilename);
    setStyleSheet(getStyles());
    selectedRadioBtm = "light";
    writeSettings();
}

void SettingsForm::on_rBtmDark_clicked(bool )
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = ":/Styles/dark.qss";
    StylesStr = loadStyle(StyleFilename);
    setStyleSheet(getStyles());
    selectedRadioBtm = "dark";
    writeSettings();
}

void SettingsForm::on_rBtmDefoult_clicked(bool )
{
    ui->btmStyle->setEnabled(false);
    StyleFilename = "";
    StylesStr = "";
    setStyleSheet(getStyles());
    selectedRadioBtm = "defoult";
    writeSettings();
}

void SettingsForm::on_btmSManager_clicked()
{
    SentenceManagerForm *form = new SentenceManagerForm();
    //this->hide();
    form->exec();
    //this->show();
}

void SettingsForm::on_fontComboBox_currentFontChanged(const QFont &f)
{
    font = f;
    writeSettings();
    setStyleSheet(getStyles());
}

QString SettingsForm::loadStyle(QString filename)
{
    QFile* file = new QFile(filename);
    if(!file->exists())
        return "";
    file->open(QIODevice::ReadOnly);
    QTextStream* in = new QTextStream(file);
    QString res = in->readAll();
    file->close();
    return res;
}

void SettingsForm::on_spinBox_editingFinished()
{
    WordsCount = ui->spinBox->value();
    writeSettings();
}
