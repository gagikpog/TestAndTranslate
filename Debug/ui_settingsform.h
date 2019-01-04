/********************************************************************************
** Form generated from reading UI file 'settingsform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSFORM_H
#define UI_SETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsForm
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *rBtmDark;
    QRadioButton *rBtmLight;
    QRadioButton *rBtmCustom;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btmStyle;

    void setupUi(QDialog *SettingsForm)
    {
        if (SettingsForm->objectName().isEmpty())
            SettingsForm->setObjectName(QStringLiteral("SettingsForm"));
        SettingsForm->resize(695, 537);
        SettingsForm->setStyleSheet(QLatin1String("QWidget {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #ddd);\n"
"color: #000;\n"
"}\n"
"QPushButton:!enabled {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #fff);\n"
"border: 1px solid #bbb\n"
"}\n"
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
"}"));
        widget = new QWidget(SettingsForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 131, 184, 93));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rBtmDark = new QRadioButton(widget);
        rBtmDark->setObjectName(QStringLiteral("rBtmDark"));
        QFont font;
        font.setPointSize(13);
        rBtmDark->setFont(font);

        verticalLayout->addWidget(rBtmDark);

        rBtmLight = new QRadioButton(widget);
        rBtmLight->setObjectName(QStringLiteral("rBtmLight"));
        rBtmLight->setFont(font);

        verticalLayout->addWidget(rBtmLight);

        rBtmCustom = new QRadioButton(widget);
        rBtmCustom->setObjectName(QStringLiteral("rBtmCustom"));
        rBtmCustom->setFont(font);

        verticalLayout->addWidget(rBtmCustom);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btmStyle = new QPushButton(widget);
        btmStyle->setObjectName(QStringLiteral("btmStyle"));

        verticalLayout_2->addWidget(btmStyle);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(SettingsForm);

        QMetaObject::connectSlotsByName(SettingsForm);
    } // setupUi

    void retranslateUi(QDialog *SettingsForm)
    {
        SettingsForm->setWindowTitle(QApplication::translate("SettingsForm", "Dialog", Q_NULLPTR));
        rBtmDark->setText(QApplication::translate("SettingsForm", "Dar&k", Q_NULLPTR));
        rBtmLight->setText(QApplication::translate("SettingsForm", "&Light", Q_NULLPTR));
        rBtmCustom->setText(QApplication::translate("SettingsForm", "Custom", Q_NULLPTR));
        btmStyle->setText(QApplication::translate("SettingsForm", "Load Style", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingsForm: public Ui_SettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSFORM_H
