#include "feedback.h"
#include "ui_feedback.h"
#include "settingsform.h"
#include "header.h"
#include "mainwindow.h"
#include "loggingcategories.h"

Feedback::Feedback(QWidget *parent) : QDialog(parent), ui(new Ui::Feedback)
{
    ui->setupUi(this);
    //задать стиль окна
    setStyleSheet(SettingsForm::getStyles());
    setInterfaceLanguage(SettingsForm::ApplicationLanguage);
}

Feedback::~Feedback()
{
    delete ui;
}

void Feedback::setInterfaceLanguage(QString lang)
{
    if (lang == "ru")
    {
        ui->btnClose->setText("&Выход");
        ui->btnSend->setText("&Отправить");
        this->setWindowTitle("Обратная связь");
        msgBoxWarning = "Ошибка при отправке отзыва";
        msgBoxTitle = "Ошибка";
    }
}

void Feedback::on_textEdit_textChanged()
{
    if (ui->textEdit->toPlainText().length() > 240) {
        ui->textEdit->textCursor().deletePreviousChar();
    }
    ui->lblInfo->setText( QString::number(ui->textEdit->toPlainText().length())+ "/240");
}

void Feedback::on_btnSend_clicked()
{
    //готовлюсь к отправке запроса
    QNetworkAccessManager *NAM = new QNetworkAccessManager(this);
    //назначаю процедуру для подучения ответа
    connect(NAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    //сервер
    QString hostPage =  SettingsForm::Host + "/translate/feedback.php";
    //из строки в формате json нужно достать name, sname и group
    QJsonObject root = QJsonDocument::fromJson(MainWindow::User.toUtf8()).object();

    QString name = root.value("name").toString() + " " + root.value("sname").toString();
    QString group = root.value("group").toString();
    QString msg = ui->textEdit->toPlainText();
    //делаем экранирование текста
    QString programmVersion = QUrl::toPercentEncoding(VERSION);
    name = QUrl::toPercentEncoding(name);
    group = QUrl::toPercentEncoding(group);
    msg = QUrl::toPercentEncoding(msg);
    //составляем параметры запроса
    QString params = "?name=" + name + "&group=" + group + "&msg=" + msg + "&version=" + programmVersion;
    QString url = hostPage + params;
    qDebug(logDebug()) << "Feedback form sending";
    qDebug(logDebug()) << "send feedback: " << url;
    //отправляю get запрос
    NAM->get(QNetworkRequest(url));
}


//процедура которая вызывается для приема ответа от сервера
void Feedback::replyFinished(QNetworkReply* reply)
{
    //преобразование полученных данных в массив байт
    QByteArray response = reply->readAll();
    //получаем из его Q строку
    QString DataAsString = QString::fromStdString(response.toStdString());
    if (DataAsString == "done\n")
    {
        //пришел ответ от сервера что отзыв принят
        qDebug(logDebug()) << "Feedback form sending: Done";
        this->close();
    } else {
        //не удалось соеденится с сервером или возникла ошибка на сервере
        qDebug(logDebug()) << "Feedback form sending: Error";
        qDebug(logDebug()) << "server resoult: " << DataAsString;

        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle(msgBoxTitle);

        msgBox->setText(msgBoxWarning);
        msgBox->exec();
    }
}
