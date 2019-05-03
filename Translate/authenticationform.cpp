#include "authenticationform.h"
#include "ui_authenticationform.h"
#include "settingsform.h"

AuthenticationForm::AuthenticationForm(QWidget *parent) :QDialog(parent),ui(new Ui::AuthenticationForm)
{
   ui->setupUi(this);
   //задать заголовок окна
   setWindowTitle("Authentication");
   //задать язык нитерфейса
   setInterfaceLanguage(SettingsForm::ApplicationLanguage);
   //загрузить симли
   setStyleSheet(SettingsForm::getStyles());
   //регулярное выражение для миен
   regName = new QRegExp ("[A-Z]{1}[a-z]{1,}|[А-Я]{1}[а-я]{1,}");
   //регулярное выражение для групп
   regGroup = new QRegExp ("([A-Z]{2,3}|[a-z]{2,3}|[а-я]{2,3}|[А-Я]{2,3})-\\d{3}");
   //создаем шаблон имен
   QRegExpValidator *validator1 = new QRegExpValidator(*regName, this);
   //задаем шаблон имен
   ui->editName->setValidator(validator1);
   ui->editSName->setValidator(validator1);
   //создаем шаблон груп
   QRegExpValidator *validator2 = new QRegExpValidator(*regGroup, this);
   //задаем шаблон имен
   ui->editGroup->setValidator(validator2);
}

AuthenticationForm::~AuthenticationForm()
{
   delete ui;
}

void AuthenticationForm::setInterfaceLanguage(QString lang)
{
   //задать язык интерфейса
   if(lang == "ru")
   {
       strPass = "Пароль";
       strGroup = "Группа";
       ui->lblTitle->setText("Введите свое имя и группу, чтобы продолжить.");
       ui->lblGroup->setText(strGroup);
       ui->lblName->setText("Имя");
       ui->lblSName->setText("Фамилия");
       ui->btmSingIn->setText("&Войти");
       setWindowTitle("Аутентификация");
   }
}

QString AuthenticationForm::getAuthData()
{
   //возвращает данные пользователя в формате json
   return "{ \"name\": \""+ui->editName->text()+"\", \"sname\": \""+ui->editSName->text()+"\", \"group\": \""+ui->editGroup->text()+"\" }";
}

void AuthenticationForm::on_btmSingIn_clicked()
{
   //проверка и изменения цвета в пустых или неправильно заполненных полях
   editsUpdate();
   //если текст введен неправильно то передать фокус в поле ввода и выйти
   if (!regName->exactMatch(ui->editName->text()))
   {
       ui->editName->setFocus();
       return;
   }
   //если текст введен неправильно то передать фокус в поле ввода и выйти
   if(!regName->exactMatch(ui->editSName->text()))
   {
       ui->editSName->setFocus();
       return;
   }

   if(ui->editGroup->text() != "sqlite18")
   {
       //если текст введен неправильно то передать фокус в поле ввода и выйти
       if(!regGroup->exactMatch(ui->editGroup->text()))
       {

           ui->editGroup->setFocus();
           return;
       }
   }


   //авторизация прошла успешно
   auth = true;
   //закрыть окно
   close();
}

void AuthenticationForm::editsUpdate()
{
   //если текст введен неправильно то сделать фон красным иначе сбросить стили
   if(!regName->exactMatch(ui->editName->text()))
       ui->editName->setStyleSheet("background: #FF313E;");
   else ui->editName->setStyleSheet("");
   //если текст введен неправильно то сделать фон красным иначе сбросить стили
   if(!regName->exactMatch(ui->editSName->text()))
       ui->editSName->setStyleSheet("background: #FF313E;");
   else ui->editSName->setStyleSheet("");
   //если текст введен неправильно то сделать фон красным иначе сбросить стили
   if(!regGroup->exactMatch(ui->editGroup->text()))
       ui->editGroup->setStyleSheet("background: #FF313E;");
   else ui->editGroup->setStyleSheet("");

   if(ui->editName->text() == "Admin" && ui->editSName->text() == "Admin"){
       ui->editGroup->setStyleSheet("");
       ui->editGroup->setValidator(NULL);
       ui->editGroup->setEchoMode(QLineEdit::Password);
       ui->lblGroup->setText(strPass);
   }else {
       if(ui->editGroup->echoMode() == QLineEdit::Normal)
       {
           return;
       }
       //создаем шаблон груп
       QRegExpValidator *validator2 = new QRegExpValidator(*regGroup, this);
       //задаем шаблон имен
       ui->editGroup->setValidator(validator2);
       ui->editGroup->setEchoMode(QLineEdit::Normal);
       ui->editGroup->setText("");
       ui->lblGroup->setText(strGroup);
   }

}
