#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :QDialog(parent), ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {

    }
}
