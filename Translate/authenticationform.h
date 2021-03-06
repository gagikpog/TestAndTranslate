#ifndef AUTHENTICATIONFORM_H
#define AUTHENTICATIONFORM_H

#include <QDialog>
#include <QRegExpValidator>

namespace Ui {
class AuthenticationForm;
}

class AuthenticationForm : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationForm(QWidget *parent = 0);
    ~AuthenticationForm();
    void setInterfaceLanguage(QString lang);
    bool isAuth(){return auth;}
    QString getAuthData();
private slots:
    void on_btmSingIn_clicked();
    void editsUpdate();
private:
    bool auth = false;
    Ui::AuthenticationForm *ui;
    QRegExp* regName;
    QRegExp* regGroup;
    QString strPass = "Password";
    QString strGroup = "Group";
};

#endif // AUTHENTICATIONFORM_H
