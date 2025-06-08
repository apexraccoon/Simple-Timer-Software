QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    timer.cpp

HEADERS += \
    timer.h

FORMS += \
    timer.ui

TRANSLATIONS += \
    Timer_Project_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
