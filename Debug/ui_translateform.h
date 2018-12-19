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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TranslateForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btmTranslate;
    QPushButton *btmFavorite;
    QPushButton *btmRemove;
    QGridLayout *gridLayout;
    QTextEdit *msgOutput;
    QTextEdit *msgInput;
    QLabel *label2;
    QPushButton *btmLanguage;
    QLabel *label1;
    QListWidget *listWidget;

    void setupUi(QDialog *TranslateForm)
    {
        if (TranslateForm->objectName().isEmpty())
            TranslateForm->setObjectName(QStringLiteral("TranslateForm"));
        TranslateForm->resize(834, 624);
        TranslateForm->setStyleSheet(QLatin1String("QWidget {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #ddd);\n"
"}\n"
"\n"
"QPushButton {\n"
"color: #000;\n"
"border: 1px solid #555;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #eee, stop: 1 #fff);\n"
"}\n"
"QPushButton:hover {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #eee, stop: 1 #ddd);\n"
"}\n"
"QPushButton:pressed {\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.3, stop: 0 #e5e5e5, stop: 1 #d5d5d5);\n"
"}\n"
"QTextEdit{\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #eee);\n"
"}\n"
"QLabel{\n"
"padding: 0px 10px;\n"
"}"));
        verticalLayout = new QVBoxLayout(TranslateForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btmTranslate = new QPushButton(TranslateForm);
        btmTranslate->setObjectName(QStringLiteral("btmTranslate"));
        btmTranslate->setMinimumSize(QSize(150, 45));
        QFont font;
        font.setPointSize(14);
        btmTranslate->setFont(font);

        horizontalLayout->addWidget(btmTranslate);

        btmFavorite = new QPushButton(TranslateForm);
        btmFavorite->setObjectName(QStringLiteral("btmFavorite"));
        btmFavorite->setMinimumSize(QSize(150, 45));
        btmFavorite->setFont(font);

        horizontalLayout->addWidget(btmFavorite);

        btmRemove = new QPushButton(TranslateForm);
        btmRemove->setObjectName(QStringLiteral("btmRemove"));
        btmRemove->setMinimumSize(QSize(150, 45));
        btmRemove->setFont(font);

        horizontalLayout->addWidget(btmRemove);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(10);
        msgOutput = new QTextEdit(TranslateForm);
        msgOutput->setObjectName(QStringLiteral("msgOutput"));
        msgOutput->setMaximumSize(QSize(16777215, 100));

        gridLayout->addWidget(msgOutput, 1, 2, 1, 1);

        msgInput = new QTextEdit(TranslateForm);
        msgInput->setObjectName(QStringLiteral("msgInput"));
        msgInput->setMaximumSize(QSize(16777215, 100));

        gridLayout->addWidget(msgInput, 1, 0, 1, 1);

        label2 = new QLabel(TranslateForm);
        label2->setObjectName(QStringLiteral("label2"));

        gridLayout->addWidget(label2, 0, 2, 1, 1);

        btmLanguage = new QPushButton(TranslateForm);
        btmLanguage->setObjectName(QStringLiteral("btmLanguage"));
        btmLanguage->setMinimumSize(QSize(30, 30));
        btmLanguage->setMaximumSize(QSize(30, 30));
        btmLanguage->setStyleSheet(QLatin1String("QPushButton{\n"
"border-radius: 15px;\n"
"border: 2px solid #555\n"
"}"));
        btmLanguage->setAutoDefault(false);

        gridLayout->addWidget(btmLanguage, 0, 1, 1, 1);

        label1 = new QLabel(TranslateForm);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(label1, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        listWidget = new QListWidget(TranslateForm);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);


        retranslateUi(TranslateForm);

        QMetaObject::connectSlotsByName(TranslateForm);
    } // setupUi

    void retranslateUi(QDialog *TranslateForm)
    {
        TranslateForm->setWindowTitle(QApplication::translate("TranslateForm", "Dialog", Q_NULLPTR));
        btmTranslate->setText(QApplication::translate("TranslateForm", "Translate", Q_NULLPTR));
        btmFavorite->setText(QApplication::translate("TranslateForm", "Favorite", Q_NULLPTR));
        btmRemove->setText(QApplication::translate("TranslateForm", "Remove", Q_NULLPTR));
        label2->setText(QApplication::translate("TranslateForm", "Russian", Q_NULLPTR));
        btmLanguage->setText(QApplication::translate("TranslateForm", "\360\237\227\230", Q_NULLPTR));
        label1->setText(QApplication::translate("TranslateForm", "English", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TranslateForm: public Ui_TranslateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATEFORM_H
