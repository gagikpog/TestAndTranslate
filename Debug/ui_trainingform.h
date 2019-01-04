/********************************************************************************
** Form generated from reading UI file 'trainingform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAININGFORM_H
#define UI_TRAININGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TrainingForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btmCheck;
    QPushButton *btmNext;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QListWidget *list1;
    QListWidget *list2;
    QLabel *labelStatus;

    void setupUi(QDialog *TrainingForm)
    {
        if (TrainingForm->objectName().isEmpty())
            TrainingForm->setObjectName(QStringLiteral("TrainingForm"));
        TrainingForm->resize(606, 616);
        TrainingForm->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(TrainingForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btmCheck = new QPushButton(TrainingForm);
        btmCheck->setObjectName(QStringLiteral("btmCheck"));
        btmCheck->setMinimumSize(QSize(150, 40));
        QFont font;
        font.setPointSize(14);
        btmCheck->setFont(font);

        horizontalLayout_2->addWidget(btmCheck);

        btmNext = new QPushButton(TrainingForm);
        btmNext->setObjectName(QStringLiteral("btmNext"));
        btmNext->setMinimumSize(QSize(150, 40));
        btmNext->setFont(font);

        horizontalLayout_2->addWidget(btmNext);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        list1 = new QListWidget(TrainingForm);
        list1->setObjectName(QStringLiteral("list1"));
        list1->setMinimumSize(QSize(200, 300));
        QFont font1;
        font1.setPointSize(12);
        list1->setFont(font1);

        horizontalLayout->addWidget(list1);

        list2 = new QListWidget(TrainingForm);
        list2->setObjectName(QStringLiteral("list2"));
        list2->setMinimumSize(QSize(200, 300));
        list2->setFont(font1);
        list2->setWordWrap(true);
        list2->setSortingEnabled(true);

        horizontalLayout->addWidget(list2);


        verticalLayout->addLayout(horizontalLayout);

        labelStatus = new QLabel(TrainingForm);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(labelStatus);

        QWidget::setTabOrder(btmCheck, btmNext);
        QWidget::setTabOrder(btmNext, list1);
        QWidget::setTabOrder(list1, list2);

        retranslateUi(TrainingForm);

        QMetaObject::connectSlotsByName(TrainingForm);
    } // setupUi

    void retranslateUi(QDialog *TrainingForm)
    {
        TrainingForm->setWindowTitle(QApplication::translate("TrainingForm", "Dialog", Q_NULLPTR));
        btmCheck->setText(QApplication::translate("TrainingForm", "Check", Q_NULLPTR));
        btmNext->setText(QApplication::translate("TrainingForm", "Next", Q_NULLPTR));
        labelStatus->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TrainingForm: public Ui_TrainingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAININGFORM_H
