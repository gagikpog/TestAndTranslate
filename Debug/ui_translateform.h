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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TranslateForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *msgInput;
    QPushButton *btmLanguage;
    QLabel *msgOutput;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btmTranslate;
    QPushButton *btmFavorite;
    QPushButton *btmRemove;
    QListWidget *listWidget;

    void setupUi(QDialog *TranslateForm)
    {
        if (TranslateForm->objectName().isEmpty())
            TranslateForm->setObjectName(QStringLiteral("TranslateForm"));
        TranslateForm->resize(834, 624);
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
        verticalLayout_3 = new QVBoxLayout(TranslateForm);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        msgInput = new QLineEdit(TranslateForm);
        msgInput->setObjectName(QStringLiteral("msgInput"));
        msgInput->setMinimumSize(QSize(0, 45));

        horizontalLayout_2->addWidget(msgInput);

        btmLanguage = new QPushButton(TranslateForm);
        btmLanguage->setObjectName(QStringLiteral("btmLanguage"));
        btmLanguage->setMinimumSize(QSize(0, 45));
        btmLanguage->setAutoDefault(false);

        horizontalLayout_2->addWidget(btmLanguage);


        verticalLayout->addLayout(horizontalLayout_2);

        msgOutput = new QLabel(TranslateForm);
        msgOutput->setObjectName(QStringLiteral("msgOutput"));

        verticalLayout->addWidget(msgOutput);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        btmTranslate = new QPushButton(TranslateForm);
        btmTranslate->setObjectName(QStringLiteral("btmTranslate"));
        btmTranslate->setMinimumSize(QSize(150, 45));

        verticalLayout_2->addWidget(btmTranslate);

        btmFavorite = new QPushButton(TranslateForm);
        btmFavorite->setObjectName(QStringLiteral("btmFavorite"));
        btmFavorite->setMinimumSize(QSize(150, 45));

        verticalLayout_2->addWidget(btmFavorite);

        btmRemove = new QPushButton(TranslateForm);
        btmRemove->setObjectName(QStringLiteral("btmRemove"));
        btmRemove->setMinimumSize(QSize(150, 45));

        verticalLayout_2->addWidget(btmRemove);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        listWidget = new QListWidget(TranslateForm);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_3->addWidget(listWidget);


        retranslateUi(TranslateForm);

        QMetaObject::connectSlotsByName(TranslateForm);
    } // setupUi

    void retranslateUi(QDialog *TranslateForm)
    {
        TranslateForm->setWindowTitle(QApplication::translate("TranslateForm", "Dialog", Q_NULLPTR));
        btmLanguage->setText(QApplication::translate("TranslateForm", "\320\240\320\243-EN", Q_NULLPTR));
        msgOutput->setText(QString());
        btmTranslate->setText(QApplication::translate("TranslateForm", "Translate", Q_NULLPTR));
        btmFavorite->setText(QApplication::translate("TranslateForm", "Favorite", Q_NULLPTR));
        btmRemove->setText(QApplication::translate("TranslateForm", "Remove", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TranslateForm: public Ui_TranslateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATEFORM_H
