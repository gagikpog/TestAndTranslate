#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QFile>
#include <QProcess>
#include <QDir>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setInterfaceLanguage(QString lang= "ru");
    static QString User;
private slots:
    void on_btmTranslate_clicked();
    void on_btmLanguage_clicked();
    void on_btmTraining_clicked();
    void on_btmSetting_clicked();
    void on_btmPuzzle_clicked();
    void on_lblUser_linkActivated(const QString &link);
    bool UserAuth(bool forcibly = false);

private:
    Ui::MainWindow *ui;
    QTimer* tmr;
};
#endif // MAINWINDOW_H
