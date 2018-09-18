// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvwidget.h"
#include <QApplication>
#include <QDebug>
#include <QDateTime>

void initApp()
{
    qDebug() << "Qt Widget Stub for OpenCV";
    qDebug() << QDateTime::currentDateTime();
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "msec since Epoch";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initApp();
    CvWidget w;
    w.show();

    return a.exec();
}
