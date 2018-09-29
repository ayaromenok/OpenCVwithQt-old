// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "qcvobject.h"
#include "../share/share.h"
#include <opencv/cv.hpp>

QCvObject::QCvObject(QObject *parent) : QObject(parent)
{
    CVQT_TIMESTAMP();
    cv::Point2f testP2f(1.67f, 3.1415f);
    qDebug() << "cv::Point2f" << testP2f.x << testP2f.y;
    _intVal = 0;
}

QCvObject::~QCvObject()
{
    CVQT_TIMESTAMP();
}


int
QCvObject::intVal()
{
    CVQT_TIMESTAMP();

    return _intVal;
}

void
QCvObject::setIntVal(int value)
{
    CVQT_TIMESTAMP();

    _intVal = value;
}
