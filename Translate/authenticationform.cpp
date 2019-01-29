#include "authenticationform.h"
#include "ui_authenticationform.h"
#include "settingsform.h"

AuthenticationForm::AuthenticationForm(QWidget *parent) :QDialog(parent),ui(new Ui::AuthenticationForm)
{
    ui->setupUi(this);

    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(SettingsForm::getStyles());
}

AuthenticationForm::~AuthenticationForm()
{
    delete ui;
}

void AuthenticationForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->lblGroup->setText("Группа");
        ui->lblName->setText("Имя");
        ui->lblSName->setText("Фамилия");
        ui->btmSingIn->setText("&Войти");
    }
}

void AuthenticationForm::on_btmSingIn_clicked()
{

}
