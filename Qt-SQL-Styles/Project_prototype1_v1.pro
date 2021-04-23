QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

QT += widgets
#these are to make sure I can use Qt libraries
QT += sql


INCLUDEPATH += C:\Program Files\PostgreSQL\13\include
LIBS += -L"C:\Program Files\PostgreSQL\13\lib"


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        inicio_dialog.cpp \
        main.cpp \
        principal.cpp \
        recommend_dialog.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    inicio_dialog.ui \
    recommend_dialog.ui

HEADERS += \
    inicio_dialog.h \
    principal.h \
    recommend_dialog.h

RESOURCES += \
    pics.qrc
