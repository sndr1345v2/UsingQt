#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T12:43:11
#
#-------------------------------------------------

QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bookin_Good
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


SOURCES += \
        main.cpp \
        inicio_dialog.cpp \
    registro_dialog.cpp \
    cuenta.cpp \
    principal.cpp \
    menu_dialog.cpp \
    libro.cpp

HEADERS += \
        inicio_dialog.h \
    registro_dialog.h \
    cuenta.h \
    principal.h \
    menu_dialog.h \
    libro.h

FORMS += \
        inicio_dialog.ui \
    registro_dialog.ui \
    menu_dialog.ui
