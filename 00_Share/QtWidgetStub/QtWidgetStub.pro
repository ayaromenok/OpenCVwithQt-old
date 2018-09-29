# Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
# MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

QT      += core gui widgets
QT      += multimedia multimediawidgets

TARGET = QtWidgetStub
TEMPLATE = app

CONFIG += c++11

include(../share.pri)
include(../opencv.pri)
include(android.pri)

SOURCES += \
        main.cpp \
        cvwidget.cpp

HEADERS += \
        cvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res.qrc

