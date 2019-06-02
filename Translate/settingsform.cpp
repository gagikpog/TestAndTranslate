#include "settingsform.h"
#include "sentencemanagerform.h"
#include "ui_settingsform.h"
#include "mainwindow.h"

//статические поля класса, тут настройки и конфигурации всего проекта
//название ДБ
QString SettingsForm::DatabaseName = "data.db";
//название фаела стлей
QString SettingsForm::StyleFilename = ":/Styles/dark.qss";
//язык итерфейса
QString SettingsForm::ApplicationLanguage = "en";
//кодичество слов отображающих а форме тренеровка
int SettingsForm::WordsCount = 8;
//двойной клик как кнопка "Проверка" в trainingform
QString SettingsForm::testCheckMode = "off";
//название текущего стиля
QString SettingsForm::StylesStr = "";
//названия фаела с настройкамыи
const QString SettingsForm::settingsFilename = "settings.ini";
//название шрифта
QFont SettingsForm::font;

SettingsForm::SettingsForm(QWidget *parent) :QDialog(parent), ui(new Ui::SettingsForm)
{
   ui->setupUi(this);
   //задвть заголовок окна
   setWindowTitle("Settings");
   //загружает настройки которые нужни конкретно для этого окна
   readLocakSettings();
   //задать стиль окна
   setStyleSheet(getStyles());
   //задать язык интерфейса
   setInterfaceLanguage(ApplicationLanguage);
   //указать какой шрифт сейяас выбран
   ui->fontComboBox->setCurrentFont(font);
   //задать значене "количество слов" из файла
   ui->spinBox->setValue(WordsCount);
   //начальное значение при открытии окна
   ui->testCheckModeBox->setChecked(testCheckMode == "on");

   QJsonObject root = QJsonDocument::fromJson(MainWindow::User.toUtf8()).object();
   QString tmp = root.value("group").toString();
   if(tmp != "sqlite18")
   {
        ui->btmSManager->setVisible(false);
        ui->labelWord->setVisible(false);
        ui->spinBox->setVisible(false);
   }
}

SettingsForm::~SettingsForm()
{
   delete ui;
}

void SettingsForm::setInterfaceLanguage(QString lang)
{
   //перевести интерфейс на русский
   if(lang == "ru")
   {
       ui->rBtmDark->setText("Темный");
       ui->rBtmLight->setText("Светлая");
       ui->rBtmCustom->setText("Другой");
       ui->rBtmDefoult->setText("По умолчанию");
       ui->btmStyle->setText("Загрузить стиль");
       ui->labelWord->setText("Количество слов");
       ui->labelStyle->setText("Стиль применения");
       ui->btmSManager->setText("Редактор задач");
       ui->testCheckModeBox->setText("Двойной клик - нажатие на кнопку 'Проверка'");
       setWindowTitle("Настройки");
   }
}

void SettingsForm::readSettings()
{
   //статический метод который загружает основные параметры из файла
   //объект для чтения
   QSettings settings(settingsFilename, QSettings::IniFormat);
   //загрузить стили
   StyleFilename = settings.value("styleFile", "").toString();
   //загрузить язык  интерфейса
   ApplicationLanguage = settings.value("language", "en").toString();
   //загрузить шрифты
   font.setFamily(settings.value("font", "Ubuntu").toString());
   //загрузить параметр "количество слов"
   WordsCount = settings.value("wordsCount","8").toInt();
   //загрузить парамета двойного клика как кнопка "Проверка" в trainingform
   testCheckMode = settings.value("testCheckMode","off").toString();
   //загрузить стили из файла
   StylesStr = loadStyle(StyleFilename);
}

void SettingsForm::writeLanguage()
{
   //записывает язык интерфейса в файл
   //его вынесли в отдельный метод потому что это единственный
   //параметр который меняется вне класса настройки
   //объект для записи настроек
   QSettings settings(settingsFilename, QSettings::IniFormat);
   //запить языка
   settings.setValue("language", ApplicationLanguage);
}

QString SettingsForm::getStyles()
{
   //объединяет стильы и шрифт как обший стиль (формт qss)
   return StylesStr + "QWidget{font-family: \"" + font.family() + "\";}";
}

void SettingsForm::on_btmStyle_clicked()
{
   //создается диалоговое окно
   QFileDialog* dlg = new QFileDialog(this);
   //вызывается окно и результат выбора сохраняется в переменную res
   QString res = dlg->getOpenFileName(this,"caption","Styles","Qt style files(*.qss);; All files (*.*)");
   //если был выбран файл то продолжить
   if(!res.isEmpty())
   {
       //задать файл как фаел для стилей
       StyleFilename = res;
       //загрузить стили
       StylesStr = loadStyle(StyleFilename);
       //задать стиль текущего окна
       setStyleSheet(getStyles());
       customStyleFile = res;
       //задать название сохраненного пункта
       selectedRadioBtm = "custom";
       //сохранить настройки
       writeSettings();
   }else {
       //если файл не выбран отменить выбор
       selectRadioBatton(selectedRadioBtm);
   }
}

void SettingsForm::writeSettings()
{
   //сохраняет настройки в файл
   //определяет какой пункт выбран
   QString check = "dark";
   if(ui->rBtmLight->isChecked())
       check = "light";
   if(ui->rBtmCustom->isChecked())
       check = "custom";
   if(ui->rBtmDefoult->isChecked())
       check = "defoult";
   //объект для сохранений
   QSettings settings(settingsFilename, QSettings::IniFormat);
   //поочередно сохраняет все параметры
   settings.setValue("styleFile", StyleFilename);
   settings.setValue("checkbox", check );
   settings.setValue("customStyleFile", customStyleFile);
   settings.setValue("font",font. family());
   settings.setValue("wordsCount", WordsCount);
   settings.setValue("testCheckMode", testCheckMode);
}

void SettingsForm::readLocakSettings()
{
   //загружает настройки которые нужны конкретно для этого окна
   //объект для чтения
   QSettings settings(settingsFilename, QSettings::IniFormat);
   //загружает начтройкии
   selectRadioBatton(settings.value("checkbox", "").toString());
   customStyleFile = settings.value("customStyleFile", "").toString();
}

void SettingsForm::selectRadioBatton(QString check)
{
   //переключает переключатель по его названию
   ui->rBtmDefoult->setChecked(check == "defoult");
   ui->rBtmCustom->setChecked(check == "custom");
   ui->rBtmDark->setChecked(check == "dark");
   ui->rBtmLight->setChecked(check == "light");
   ui->btmStyle->setEnabled(check == "custom");
   selectedRadioBtm = check;
}

void SettingsForm::on_rBtmCustom_clicked(bool checked)
{
   //при выпора пункта "другой"
   //кнопка "загрузить стиль" становится активной
   ui->btmStyle->setEnabled(checked);
   //если файл еще не был выбран он вызывает событие на нажатие кнопки "загрузить стиль"
   if(!QFile::exists(customStyleFile)){
       on_btmStyle_clicked();
   }else{
       //иначе
       //меняем назваеие выбранного стиля
       StyleFilename = customStyleFile;
       //загружаем стиль с файла
       StylesStr = loadStyle(StyleFilename);
       //задаем стиль текущего окна
       setStyleSheet(getStyles());
       //сохроняем настройки
       writeSettings();
   }
}

void SettingsForm::on_rBtmLight_clicked(bool )
{
   //отключаем кнопку "загрузить стиль"
   ui->btmStyle->setEnabled(false);
   //задаем файл стилей (он находится в ресурсах)
   StyleFilename = ":/Styles/light.qss";
   //загружаем стили
   StylesStr = loadStyle(StyleFilename);
   //задаем стиль текущего окна
   setStyleSheet(getStyles());
   //меняем назваеие выбранного стиля
   selectedRadioBtm = "light";
   //сохроняем настройки
   writeSettings();
}

void SettingsForm::on_rBtmDark_clicked(bool )
{
   //отключаем кнопку "загрузить стиль"
   ui->btmStyle->setEnabled(false);
   //задаем файл стилей (он находится в ресурсах)
   StyleFilename = ":/Styles/dark.qss";
   //загружаем стили
   StylesStr = loadStyle(StyleFilename);
   //задаем стиль текущего окна
   setStyleSheet(getStyles());
   //меняем название выбранного стиля
   selectedRadioBtm = "dark";
   //сохраняем настройки
   writeSettings();
}

void SettingsForm::on_rBtmDefoult_clicked(bool )
{
   ui->btmStyle->setEnabled(false);
   //задаем файл стилей (его нет)
   //это означает пустой стиль(зависит от стиля ОС)
   StyleFilename = "";
   //загружаем стили
   StylesStr = "";
   //задаем стиль текущего окна
   setStyleSheet(getStyles());
   //меняем название выбранного стиля
   selectedRadioBtm = "defoult";
   //сохроняем настройки
   writeSettings();
}

void SettingsForm::on_btmSManager_clicked()
{
   //открываем форму для редактирования предложений
   SentenceManagerForm *form = new SentenceManagerForm();
   //this->hide();
   form->exec();
   //this->show();
}

void SettingsForm::on_fontComboBox_currentFontChanged(const QFont &f)
{
   //шрифт был изменен
   font = f;
   //сохранить настройки
   writeSettings();
   //задит стиль текущего окна
   setStyleSheet(getStyles());
}

QString SettingsForm::loadStyle(QString filename)
{
   //загружает стлт из файла
   QFile* file = new QFile(filename);
   //если файл не существует то выйти
   if(!file->exists())
       return "";
   //открыть файл для чтения
   if(!file->open(QIODevice::ReadOnly))
       return "";
   //читает как текст
   QTextStream* in = new QTextStream(file);
   //загрузить все
   QString res = in->readAll();
   //закрыть файл
   file->close();
   //вернуть текст
   return res;
}

void SettingsForm::on_spinBox_editingFinished()
{
   //имененить количества слов
   WordsCount = ui->spinBox->value();
   //сохранить настройки
   writeSettings();
}

void SettingsForm::on_testCheckModeBox_clicked(bool checked)
{
    //включить/отключить режим быстрого управлением
    testCheckMode = checked ? "on" : "off";
}
