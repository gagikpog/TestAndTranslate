#include "authenticationform.h"
#include "ui_authenticationform.h"
#include "settingsform.h"

AuthenticationForm::AuthenticationForm(QWidget *parent) :QDialog(parent),ui(new Ui::AuthenticationForm)
{
    ui->setupUi(this);
    setWindowTitle("Authentication");
    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
    setStyleSheet(SettingsForm::getStyles());

    regName = new QRegExp ("[A-Z]{1}[a-z]{1,}|[А-Я]{1}[а-я]{1,}");
    regGroup = new QRegExp ("([A-Z]{2,3}|[a-z]{2,3}|[а-я]{2,3}|[А-Я]{2,3})-\\d{3}");

    QRegExpValidator *validator1 = new QRegExpValidator(*regName, this);
    ui->editName->setValidator(validator1);
    ui->editSName->setValidator(validator1);

    QRegExpValidator *validator2 = new QRegExpValidator(*regGroup, this);
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
    if (!regName->exactMatch(ui->editName->text()))
    {
        ui->editName->setFocus();
        return;
    }
    if(!regName->exactMatch(ui->editSName->text()))
    {
        ui->editSName->setFocus();
        return;
    }
    if(!regGroup->exactMatch(ui->editGroup->text()))
    {
        ui->editGroup->setFocus();
        return;
    }
    auth = true;
    close();
}

void AuthenticationForm::editsUpdate()
{
    if(!regName->exactMatch(ui->editName->text()))
        ui->editName->setStyleSheet("background: #FF313E;");
    else ui->editName->setStyleSheet("");

    if(!regName->exactMatch(ui->editSName->text()))
        ui->editSName->setStyleSheet("background: #FF313E;");
    else ui->editSName->setStyleSheet("");

    if(!regGroup->exactMatch(ui->editGroup->text()))
        ui->editGroup->setStyleSheet("background: #FF313E;");
    else ui->editGroup->setStyleSheet("");
}
