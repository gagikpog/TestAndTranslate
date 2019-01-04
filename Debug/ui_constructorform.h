/********************************************************************************
** Form generated from reading UI file 'constructorform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSTRUCTORFORM_H
#define UI_CONSTRUCTORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConstructorForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnTest;
    QPushButton *btnSkip;
    QSpacerItem *horizontalSpacer;
    QLabel *labelStatus;
    QGroupBox *frame;

    void setupUi(QDialog *ConstructorForm)
    {
        if (ConstructorForm->objectName().isEmpty())
            ConstructorForm->setObjectName(QStringLiteral("ConstructorForm"));
        ConstructorForm->resize(719, 592);
        ConstructorForm->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(ConstructorForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnTest = new QPushButton(ConstructorForm);
        btnTest->setObjectName(QStringLiteral("btnTest"));
        btnTest->setMinimumSize(QSize(200, 40));
        QFont font;
        font.setPointSize(14);
        btnTest->setFont(font);

        horizontalLayout->addWidget(btnTest);

        btnSkip = new QPushButton(ConstructorForm);
        btnSkip->setObjectName(QStringLiteral("btnSkip"));
        btnSkip->setMinimumSize(QSize(200, 40));
        btnSkip->setFont(font);

        horizontalLayout->addWidget(btnSkip);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        labelStatus = new QLabel(ConstructorForm);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setMaximumSize(QSize(16777215, 20));
        QFont font1;
        font1.setPointSize(13);
        labelStatus->setFont(font1);

        verticalLayout->addWidget(labelStatus);

        frame = new QGroupBox(ConstructorForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(700, 500));
        QFont font2;
        font2.setPointSize(14);
        font2.setKerning(true);
        frame->setFont(font2);
        frame->setAlignment(Qt::AlignCenter);
        frame->setFlat(false);
        frame->setCheckable(false);

        verticalLayout->addWidget(frame);


        retranslateUi(ConstructorForm);

        QMetaObject::connectSlotsByName(ConstructorForm);
    } // setupUi

    void retranslateUi(QDialog *ConstructorForm)
    {
        ConstructorForm->setWindowTitle(QApplication::translate("ConstructorForm", "Dialog", Q_NULLPTR));
        btnTest->setText(QApplication::translate("ConstructorForm", "Check", Q_NULLPTR));
        btnSkip->setText(QApplication::translate("ConstructorForm", "Skip", Q_NULLPTR));
        labelStatus->setText(QString());
        frame->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class ConstructorForm: public Ui_ConstructorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSTRUCTORFORM_H
