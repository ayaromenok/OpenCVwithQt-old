// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvwidget.h"
#include <QApplication>
#include "../share/share.h"

void initApp()
{
    CVQT_TIMESTAMP();

    qDebug() << QDateTime::currentMSecsSinceEpoch() << " msec since Epoch is\t"
             << QDateTime::currentDateTime();
}

int main(int argc, char *argv[])
{
    CVQT_TIMESTAMP();

    QApplication a(argc, argv);
    initApp();
    CvWidget w;
    w.show();

    return a.exec();
}
