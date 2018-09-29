// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvwidget.h"
#include <QApplication>
#include "../share/share.h"

#include <opencv2/opencv.hpp>

void initApp()
{
    CVQT_TIMESTAMP();

    qDebug() << QDateTime::currentMSecsSinceEpoch() << " msec since Epoch is\t"
             << QDateTime::currentDateTime();
    cv::Point2f testP2f(1.67f, 3.1415f);
    qDebug() << "cv::Point2f" << testP2f.x << testP2f.y;
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
