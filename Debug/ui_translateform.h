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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
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
    QLabel *label2;
    QPushButton *btmLanguage;
    QLabel *label1;
    QLineEdit *msgInput;
    QLineEdit *msgOutput;
    QPushButton *btmClear;
    QTableWidget *tableWidget;

    void setupUi(QDialog *TranslateForm)
    {
        if (TranslateForm->objectName().isEmpty())
            TranslateForm->setObjectName(QStringLiteral("TranslateForm"));
        TranslateForm->resize(634, 736);
        TranslateForm->setStyleSheet(QLatin1String("QWidget {\n"
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
"}\n"
"QLineEdit {\n"
"background: #eee;\n"
"border: 1px solid #999;\n"
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

        msgInput = new QLineEdit(TranslateForm);
        msgInput->setObjectName(QStringLiteral("msgInput"));
        msgInput->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(msgInput, 1, 0, 1, 1);

        msgOutput = new QLineEdit(TranslateForm);
        msgOutput->setObjectName(QStringLiteral("msgOutput"));
        msgOutput->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(msgOutput, 1, 2, 1, 1);

        btmClear = new QPushButton(TranslateForm);
        btmClear->setObjectName(QStringLiteral("btmClear"));
        btmClear->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        btmClear->setFont(font1);
        btmClear->setStyleSheet(QLatin1String("QPushButton{\n"
"border-radius: 6px;\n"
"border: 2px solid #555\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: #ff1111;\n"
"	font-weight: 500;\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: #ff6666;\n"
"	font-weight: 400;\n"
"}"));

        gridLayout->addWidget(btmClear, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tableWidget = new QTableWidget(TranslateForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 300));
        QFont font2;
        font2.setPointSize(12);
        tableWidget->setFont(font2);
        tableWidget->setAcceptDrops(false);
        tableWidget->setAutoFillBackground(false);
        tableWidget->setLineWidth(1);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setShowGrid(false);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setSortingEnabled(false);
        tableWidget->setWordWrap(true);
        tableWidget->setRowCount(0);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(0);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(tableWidget);

        QWidget::setTabOrder(btmTranslate, btmFavorite);
        QWidget::setTabOrder(btmFavorite, btmRemove);
        QWidget::setTabOrder(btmRemove, btmLanguage);
        QWidget::setTabOrder(btmLanguage, msgInput);
        QWidget::setTabOrder(msgInput, btmClear);
        QWidget::setTabOrder(btmClear, msgOutput);
        QWidget::setTabOrder(msgOutput, tableWidget);

        retranslateUi(TranslateForm);

        QMetaObject::connectSlotsByName(TranslateForm);
    } // setupUi

    void retranslateUi(QDialog *TranslateForm)
    {
        TranslateForm->setWindowTitle(QApplication::translate("TranslateForm", "Dialog", Q_NULLPTR));
        btmTranslate->setText(QApplication::translate("TranslateForm", "Translate", Q_NULLPTR));
        btmFavorite->setText(QApplication::translate("TranslateForm", "Add to Favorites", Q_NULLPTR));
        btmRemove->setText(QApplication::translate("TranslateForm", "Remove", Q_NULLPTR));
        label2->setText(QApplication::translate("TranslateForm", "Russian", Q_NULLPTR));
        btmLanguage->setText(QApplication::translate("TranslateForm", "\360\237\227\230", Q_NULLPTR));
        label1->setText(QApplication::translate("TranslateForm", "English", Q_NULLPTR));
        msgInput->setText(QString());
        msgOutput->setText(QString());
        btmClear->setText(QApplication::translate("TranslateForm", "X", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TranslateForm", "English", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TranslateForm", "Russian", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TranslateForm: public Ui_TranslateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATEFORM_H
