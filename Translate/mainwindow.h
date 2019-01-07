#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    static QString loadStyle(QString filename);
private slots:
    void on_btmTranslate_clicked();
    void on_btmLanguage_clicked();
    void on_btmTraining_clicked();
    void on_pushButton_clicked();
    void on_btmSetting_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
