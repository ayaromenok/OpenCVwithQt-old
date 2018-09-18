# Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
# MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

QT       += core gui widgets

TARGET = QtWidgetStub
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        cvwidget.cpp \
    ../share/cvres.cpp

HEADERS += \
        cvwidget.h \
    ../share/cvres.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res.qrc
