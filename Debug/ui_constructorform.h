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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConstructorForm
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QLabel *label;
    QGroupBox *frame;

    void setupUi(QDialog *ConstructorForm)
    {
        if (ConstructorForm->objectName().isEmpty())
            ConstructorForm->setObjectName(QStringLiteral("ConstructorForm"));
        ConstructorForm->resize(719, 660);
        verticalLayout = new QVBoxLayout(ConstructorForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_2 = new QPushButton(ConstructorForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(ConstructorForm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(ConstructorForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        label = new QLabel(ConstructorForm);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label);

        frame = new QGroupBox(ConstructorForm);
        frame->setObjectName(QStringLiteral("frame"));
        QFont font;
        font.setPointSize(13);
        frame->setFont(font);
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
        pushButton_2->setText(QApplication::translate("ConstructorForm", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ConstructorForm", "next", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ConstructorForm", "test", Q_NULLPTR));
        label->setText(QApplication::translate("ConstructorForm", "TextLabel", Q_NULLPTR));
        frame->setTitle(QApplication::translate("ConstructorForm", "GroupBox", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConstructorForm: public Ui_ConstructorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSTRUCTORFORM_H
