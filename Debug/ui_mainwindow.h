/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btmLanguage;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QPushButton *btmTraining;
    QPushButton *btmTranslate;
    QPushButton *btmSetting;
    QPushButton *btmExit;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(485, 649);
        MainWindow->setMinimumSize(QSize(400, 0));
        MainWindow->setMaximumSize(QSize(600, 800));
        QFont font;
        font.setFamily(QStringLiteral("Carlito"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QPalette palette;
        QRadialGradient gradient(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient.setSpread(QGradient::PadSpread);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0, QColor(255, 255, 255, 255));
        gradient.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush(gradient);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QRadialGradient gradient1(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient1.setSpread(QGradient::PadSpread);
        gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient1.setColorAt(0, QColor(255, 255, 255, 255));
        gradient1.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush1(gradient1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QRadialGradient gradient2(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient2.setSpread(QGradient::PadSpread);
        gradient2.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient2.setColorAt(0, QColor(255, 255, 255, 255));
        gradient2.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush2(gradient2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        QRadialGradient gradient3(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient3.setSpread(QGradient::PadSpread);
        gradient3.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient3.setColorAt(0, QColor(255, 255, 255, 255));
        gradient3.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush3(gradient3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        QRadialGradient gradient4(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient4.setSpread(QGradient::PadSpread);
        gradient4.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient4.setColorAt(0, QColor(255, 255, 255, 255));
        gradient4.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush4(gradient4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        QRadialGradient gradient5(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient5.setSpread(QGradient::PadSpread);
        gradient5.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient5.setColorAt(0, QColor(255, 255, 255, 255));
        gradient5.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush5(gradient5);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        QRadialGradient gradient6(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient6.setSpread(QGradient::PadSpread);
        gradient6.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient6.setColorAt(0, QColor(255, 255, 255, 255));
        gradient6.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush6(gradient6);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        QRadialGradient gradient7(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient7.setSpread(QGradient::PadSpread);
        gradient7.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient7.setColorAt(0, QColor(255, 255, 255, 255));
        gradient7.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush7(gradient7);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        QRadialGradient gradient8(0.3, -0.4, 1.3, 0.3, -0.4);
        gradient8.setSpread(QGradient::PadSpread);
        gradient8.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient8.setColorAt(0, QColor(255, 255, 255, 255));
        gradient8.setColorAt(1, QColor(221, 221, 221, 255));
        QBrush brush8(gradient8);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        centralWidget->setPalette(palette);
        centralWidget->setStyleSheet(QLatin1String("QWidget {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.3, stop: 0 #fff, stop: 1 #ddd);\n"
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
"border-radius:17px;\n"
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
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btmLanguage = new QPushButton(centralWidget);
        btmLanguage->setObjectName(QStringLiteral("btmLanguage"));
        btmLanguage->setMinimumSize(QSize(40, 40));
        btmLanguage->setMaximumSize(QSize(40, 40));

        horizontalLayout_2->addWidget(btmLanguage);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(300, 90));
        pushButton->setMaximumSize(QSize(400, 100));
        QFont font1;
        font1.setPointSize(18);
        pushButton->setFont(font1);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setMouseTracking(false);
        pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(pushButton);

        btmTraining = new QPushButton(centralWidget);
        btmTraining->setObjectName(QStringLiteral("btmTraining"));
        btmTraining->setMinimumSize(QSize(300, 90));
        btmTraining->setMaximumSize(QSize(400, 100));
        btmTraining->setFont(font1);
        btmTraining->setCursor(QCursor(Qt::PointingHandCursor));
        btmTraining->setMouseTracking(false);
        btmTraining->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(btmTraining);

        btmTranslate = new QPushButton(centralWidget);
        btmTranslate->setObjectName(QStringLiteral("btmTranslate"));
        btmTranslate->setMinimumSize(QSize(300, 90));
        btmTranslate->setMaximumSize(QSize(400, 100));
        btmTranslate->setFont(font1);
        btmTranslate->setCursor(QCursor(Qt::PointingHandCursor));
        btmTranslate->setMouseTracking(false);
        btmTranslate->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(btmTranslate);

        btmSetting = new QPushButton(centralWidget);
        btmSetting->setObjectName(QStringLiteral("btmSetting"));
        btmSetting->setMinimumSize(QSize(300, 90));
        btmSetting->setMaximumSize(QSize(400, 100));
        btmSetting->setFont(font1);
        btmSetting->setCursor(QCursor(Qt::PointingHandCursor));
        btmSetting->setMouseTracking(false);
        btmSetting->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(btmSetting);

        btmExit = new QPushButton(centralWidget);
        btmExit->setObjectName(QStringLiteral("btmExit"));
        btmExit->setMinimumSize(QSize(300, 90));
        btmExit->setMaximumSize(QSize(400, 100));
        btmExit->setFont(font1);
        btmExit->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(btmExit);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(pushButton, btmTraining);
        QWidget::setTabOrder(btmTraining, btmTranslate);
        QWidget::setTabOrder(btmTranslate, btmSetting);
        QWidget::setTabOrder(btmSetting, btmExit);
        QWidget::setTabOrder(btmExit, btmLanguage);

        retranslateUi(MainWindow);
        QObject::connect(btmExit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        btmLanguage->setText(QApplication::translate("MainWindow", "\320\240\320\243", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        btmTraining->setText(QApplication::translate("MainWindow", "Training", Q_NULLPTR));
        btmTranslate->setText(QApplication::translate("MainWindow", "Translate", Q_NULLPTR));
        btmSetting->setText(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        btmExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
