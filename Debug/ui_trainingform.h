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
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TrainingForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QListView *listView_2;
    QLabel *label;

    void setupUi(QDialog *TrainingForm)
    {
        if (TrainingForm->objectName().isEmpty())
            TrainingForm->setObjectName(QStringLiteral("TrainingForm"));
        TrainingForm->resize(606, 616);
        TrainingForm->setStyleSheet(QLatin1String("QWidget {\n"
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
        verticalLayout = new QVBoxLayout(TrainingForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(TrainingForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(150, 40));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(TrainingForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(150, 40));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listView = new QListView(TrainingForm);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setMinimumSize(QSize(250, 450));

        horizontalLayout->addWidget(listView);

        listView_2 = new QListView(TrainingForm);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setMinimumSize(QSize(250, 450));

        horizontalLayout->addWidget(listView_2);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(TrainingForm);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(label);


        retranslateUi(TrainingForm);

        QMetaObject::connectSlotsByName(TrainingForm);
    } // setupUi

    void retranslateUi(QDialog *TrainingForm)
    {
        TrainingForm->setWindowTitle(QApplication::translate("TrainingForm", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TrainingForm", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("TrainingForm", "PushButton", Q_NULLPTR));
        label->setText(QApplication::translate("TrainingForm", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TrainingForm: public Ui_TrainingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAININGFORM_H
