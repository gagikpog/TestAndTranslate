#-------------------------------------------------
#
# Project created by QtCreator 2018-12-17T11:00:09
#
#-------------------------------------------------

VERSION = 1.0.0.0

QT       += core gui widgets
QT       += network
QT       += sql
QT       += printsupport
!win32:QT+= webkit webkitwidgets

#icon for programm (only windows)
win32:RC_ICONS += translate.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translate
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

!win32:SOURCES += certificateform.cpp

!win32:HEADERS += certificateform.h

!win32:FORMS   += certificateform.ui

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    translateform.cpp \
    trainingform.cpp \
    constructorform.cpp \
    word.cpp \
    settingsform.cpp \
    sentencemanagerform.cpp \
    readerform.cpp \
    linefeed.cpp \
    loggingcategories.cpp \
    authenticationform.cpp

HEADERS += \
        mainwindow.h \
    translateform.h \
    trainingform.h \
    constructorform.h \
    word.h \
    settingsform.h \
    sentencemanagerform.h \
    readerform.h \
    linefeed.h \
    loggingcategories.h \
    header.h \
    authenticationform.h

FORMS += \
        mainwindow.ui \
    translateform.ui \
    trainingform.ui \
    constructorform.ui \
    settingsform.ui \
    sentencemanagerform.ui \
    readerform.ui \
    authenticationform.ui

RESOURCES += \
    resourses.qrc
