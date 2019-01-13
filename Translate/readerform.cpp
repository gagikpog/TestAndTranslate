#include "readerform.h"
#include "ui_readerform.h"
#include "settingsform.h"

ReaderForm::ReaderForm(QWidget *parent) : QDialog(parent), ui(new Ui::ReaderForm)
{
    ui->setupUi(this);
    //задать заголовок окна
    setWindowTitle("Editor");
    //задать язык интерфейса
    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
}

void ReaderForm::setInterfaceLanguage(QString lang)
{
    //меняет язык интерфейса на русский
    if(lang == "ru")
    {
        ui->btmCancel->setText("&Отмена");
        ui->btmOk->setText("&Сохранить");
        setWindowTitle("Редактор");
    }
}

void ReaderForm::setText(QString txt)
{
    //задает текст который  нужно редактировать
    ui->textEdit->setText(txt);
}

bool ReaderForm::isChanged() const
{
    //указывает на то были ли сохранены изменения
    return changed;
}

QString ReaderForm::Text() const
{
    //возвращает текст введенный пользователем
    QString txt = ui->textEdit->toPlainText();
    //удаляются все лишние пробелы
    txt = txt.simplified();
    return txt;
}

ReaderForm::~ReaderForm()
{
    delete ui;
}

void ReaderForm::on_btmOk_clicked()
{
    //применить изменения и выйти
    changed = true;
    close();
}
