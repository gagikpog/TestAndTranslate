#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translateform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
   TranslateForm *trForm = new TranslateForm();
   this->hide();
   trForm->exec();
   this->show();
}
