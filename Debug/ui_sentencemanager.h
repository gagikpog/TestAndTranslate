/********************************************************************************
** Form generated from reading UI file 'sentencemanager.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENTENCEMANAGER_H
#define UI_SENTENCEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SentenceManager
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *SentenceManager)
    {
        if (SentenceManager->objectName().isEmpty())
            SentenceManager->setObjectName(QStringLiteral("SentenceManager"));
        SentenceManager->resize(615, 480);
        verticalLayout = new QVBoxLayout(SentenceManager);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidget = new QTreeWidget(SentenceManager);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        pushButton = new QPushButton(SentenceManager);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(SentenceManager);

        QMetaObject::connectSlotsByName(SentenceManager);
    } // setupUi

    void retranslateUi(QDialog *SentenceManager)
    {
        SentenceManager->setWindowTitle(QApplication::translate("SentenceManager", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SentenceManager", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SentenceManager: public Ui_SentenceManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENTENCEMANAGER_H
