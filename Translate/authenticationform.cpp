#include "authenticationform.h"
#include "ui_authenticationform.h"
#include "settingsform.h"

AuthenticationForm::AuthenticationForm(QWidget *parent) :QDialog(parent),ui(new Ui::AuthenticationForm)
{
    ui->setupUi(this);
    setWindowTitle("Authentication");
    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(SettingsForm::getStyles());
    QRegExp re1("[A-Z]{1}[a-z]*|[А-Я]{1}[а-я]*");
    QRegExpValidator *validator1 = new QRegExpValidator(re1, this);
    ui->editName->setValidator(validator1);
    ui->editSName->setValidator(validator1);
    QRegExp re2("([A-Z]{2,3}|[a-z]{2,3}|[а-я]{2,3}|[А-Я]{2,3})-\\d{3}");
    QRegExpValidator *validator2 = new QRegExpValidator(re2, this);
    ui->editGroup->setValidator(validator2);
}

AuthenticationForm::~AuthenticationForm()
{
    delete ui;
}

void AuthenticationForm::setInterfaceLanguage(QString lang)
{
    if(lang == "ru")
    {
        ui->lblTitle->setText("Введите свое имя и группу, чтобы продолжить.");
        ui->lblGroup->setText("Группа");
        ui->lblName->setText("Имя");
        ui->lblSName->setText("Фамилия");
        ui->btmSingIn->setText("&Войти");
        setWindowTitle("Аутентификация");
    }
}

QString AuthenticationForm::getAuthData()
{
    return "{ 'name': '"+ui->editName->text()+"', 'sname': '"+ui->editSName->text()+"','group': '"+ui->editGroup->text()+"' }";
}

void AuthenticationForm::on_btmSingIn_clicked()
{
    editsUpdate();
    if(ui->editName->text().isEmpty())
    {
        ui->editName->setFocus();
        return;
    }
    if(ui->editSName->text().isEmpty())
    {
        ui->editSName->setFocus();
        return;
    }
    if(ui->editGroup->text().isEmpty())
    {
        ui->editGroup->setFocus();
        return;
    }
    auth = true;
    close();
}

void AuthenticationForm::editsUpdate()
{
    if(ui->editGroup->text().isEmpty())
        ui->editGroup->setStyleSheet("background: #FF313E;");
    else ui->editGroup->setStyleSheet("");

    if(ui->editSName->text().isEmpty())
        ui->editSName->setStyleSheet("background: #FF313E;");
    else ui->editSName->setStyleSheet("");

    if(ui->editName->text().isEmpty())
        ui->editName->setStyleSheet("background: #FF313E;");
    else ui->editName->setStyleSheet("");
}
