/********************************************************************************
** Form generated from reading UI file 'translateform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSLATEFORM_H
#define UI_TRANSLATEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TranslateForm
{
public:
    QPushButton *pushButton;
    QLabel *msgOutput;
    QLineEdit *msgInput;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QDialog *TranslateForm)
    {
        if (TranslateForm->objectName().isEmpty())
            TranslateForm->setObjectName(QStringLiteral("TranslateForm"));
        TranslateForm->resize(615, 457);
        TranslateForm->setStyleSheet(QLatin1String("QWidget {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #aaa);\n"
"}\n"
"\n"
"QLineEdit, QPushButton {\n"
"color: #000;\n"
"border: 2px solid #555;\n"
"border-radius: 17px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #ccc);\n"
"}\n"
"QLineEdit:hover ,QPushButton:hover {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #fff);\n"
"}\n"
"QPushButton:pressed {\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.3, stop: 0 #eee, stop: 1 #aaa);\n"
"}\n"
"QLabel{\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #eee);\n"
"}"));
        pushButton = new QPushButton(TranslateForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(490, 10, 121, 41));
        msgOutput = new QLabel(TranslateForm);
        msgOutput->setObjectName(QStringLiteral("msgOutput"));
        msgOutput->setGeometry(QRect(10, 60, 431, 51));
        msgInput = new QLineEdit(TranslateForm);
        msgInput->setObjectName(QStringLiteral("msgInput"));
        msgInput->setGeometry(QRect(10, 10, 431, 41));
        pushButton_2 = new QPushButton(TranslateForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(490, 60, 121, 41));
        listWidget = new QListWidget(TranslateForm);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 180, 591, 261));
        pushButton_3 = new QPushButton(TranslateForm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(490, 110, 121, 41));
        pushButton_4 = new QPushButton(TranslateForm);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(360, 120, 121, 41));

        retranslateUi(TranslateForm);

        QMetaObject::connectSlotsByName(TranslateForm);
    } // setupUi

    void retranslateUi(QDialog *TranslateForm)
    {
        TranslateForm->setWindowTitle(QApplication::translate("TranslateForm", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TranslateForm", "Translate", Q_NULLPTR));
        msgOutput->setText(QString());
        pushButton_2->setText(QApplication::translate("TranslateForm", "Favorite", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("TranslateForm", "Remove", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("TranslateForm", "\320\240\320\243-EN", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TranslateForm: public Ui_TranslateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATEFORM_H
