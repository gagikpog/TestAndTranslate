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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *rBtmDefoult;
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
        SettingsForm->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(SettingsForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 218, 122));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rBtmDefoult = new QRadioButton(layoutWidget);
        rBtmDefoult->setObjectName(QStringLiteral("rBtmDefoult"));

        verticalLayout->addWidget(rBtmDefoult);

        rBtmDark = new QRadioButton(layoutWidget);
        rBtmDark->setObjectName(QStringLiteral("rBtmDark"));
        QFont font;
        font.setPointSize(13);
        rBtmDark->setFont(font);

        verticalLayout->addWidget(rBtmDark);

        rBtmLight = new QRadioButton(layoutWidget);
        rBtmLight->setObjectName(QStringLiteral("rBtmLight"));
        rBtmLight->setFont(font);

        verticalLayout->addWidget(rBtmLight);

        rBtmCustom = new QRadioButton(layoutWidget);
        rBtmCustom->setObjectName(QStringLiteral("rBtmCustom"));
        rBtmCustom->setFont(font);

        verticalLayout->addWidget(rBtmCustom);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btmStyle = new QPushButton(layoutWidget);
        btmStyle->setObjectName(QStringLiteral("btmStyle"));

        verticalLayout_2->addWidget(btmStyle);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(SettingsForm);

        QMetaObject::connectSlotsByName(SettingsForm);
    } // setupUi

    void retranslateUi(QDialog *SettingsForm)
    {
        SettingsForm->setWindowTitle(QApplication::translate("SettingsForm", "Dialog", Q_NULLPTR));
        rBtmDefoult->setText(QApplication::translate("SettingsForm", "Defo&ult", Q_NULLPTR));
        rBtmDark->setText(QApplication::translate("SettingsForm", "Dar&k", Q_NULLPTR));
        rBtmLight->setText(QApplication::translate("SettingsForm", "&Light", Q_NULLPTR));
        rBtmCustom->setText(QApplication::translate("SettingsForm", "Custo&m", Q_NULLPTR));
        btmStyle->setText(QApplication::translate("SettingsForm", "Load Style", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingsForm: public Ui_SettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSFORM_H
