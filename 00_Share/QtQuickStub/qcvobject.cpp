// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "qcvobject.h"
#include "../share/share.h"
#include "../share/cvres.h"
#include <opencv2/opencv.hpp>
#include <QImage>

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

bool
QCvObject::edgeDetectCanny()
{
    CVQT_TIMESTAMP();
    bool result = false;
    CvQtPerf pc;

    CvRes::imageRgb();

    pc.start();
    QImage imgInQt("./imageRgb.png");
    if (!imgInQt.isNull()){
        cv::Mat imgIn, imgTmpGray, imgTmpCanny, imgOutCanny;
        imgIn = CvRes::imageQtToCv(imgInQt);
        cv::cvtColor(imgIn, imgTmpGray, cv::COLOR_RGBA2GRAY);
        cv::Canny(imgTmpGray, imgTmpCanny, 10, 100, 3, true);
        cv::cvtColor(imgTmpCanny, imgOutCanny, cv::COLOR_GRAY2BGR);
#ifdef CVQT_DEBUG_HIGHGUI
     cv::namedWindow("imgOutCanny", cv::WINDOW_AUTOSIZE);
     cv::imshow("imgOutCanny", imgOutCanny);
#endif //CVQT_DEBUG_HIGHGUI
        QImage imgOutQt;
        imgOutQt = CvRes::imageCvToQt(imgOutCanny);
        result = imgOutQt.save("./edgeDetectCanny.jpg");
    }
    pc.stop();
    return result;
}

bool
QCvObject::checkedBoardDetect()
{
    CVQT_TIMESTAMP();
    bool result = false;
    CvQtPerf pc;

    CvRes::imageChecked12x12();

    pc.start();
    QImage imgInQt("./imageChecked12x12.png");
    if (!imgInQt.isNull()){
        cv::Mat imgIn, imgTmpGray;
        imgIn = CvRes::imageQtToCv(imgInQt);
        cv::cvtColor(imgIn, imgTmpGray, cv::COLOR_RGBA2GRAY);
        std::vector<cv::Point2f> corners;
        cv::Size boardSize(12,12);
        bool found = cv::findChessboardCorners(imgTmpGray, boardSize, corners);
        if (found){
            qDebug() << "found" << corners.size();
            cv::drawChessboardCorners(imgIn, boardSize, corners, found);
        }
        //cv::cvtColor(imgTmpCanny, imgOutCanny, cv::COLOR_GRAY2BGR);
#ifdef CVQT_DEBUG_HIGHGUI
     cv::namedWindow("imgTmpGray", cv::WINDOW_AUTOSIZE);
     cv::imshow("imgTmpGray", imgTmpGray);
     cv::namedWindow("imgIn", cv::WINDOW_AUTOSIZE);
     cv::imshow("imgIn", imgIn);
#endif //CVQT_DEBUG_HIGHGUI
        QImage imgOutQt;
        imgOutQt = CvRes::imageCvToQt(imgIn);
        result = imgOutQt.save("./checkedBoardDetect.jpg");
    }
    pc.stop();
    return result;
}

bool
QCvObject::blurGaussian()
{
    CVQT_TIMESTAMP();
    bool result = false;
    CvQtPerf pc;

    CvRes::imageRgb();

    pc.start();
    QImage imgInQt("./imageRgb.png");
    if (!imgInQt.isNull()){
        cv::Mat imgIn, imgOut;
        imgIn = CvRes::imageQtToCv(imgInQt);
        cv::GaussianBlur(imgIn, imgOut, cv::Size(5,5), 3, 3);

#ifdef CVQT_DEBUG_HIGHGUI
     cv::namedWindow("imgOut", cv::WINDOW_AUTOSIZE);
     cv::imshow("imgOut", imgOut);
#endif //CVQT_DEBUG_HIGHGUI
        QImage imgOutQt;
        imgOutQt = CvRes::imageCvToQt(imgOut);
        result = imgOutQt.save("./blurGaussian.jpg");
    }
    pc.stop();
    return result;
}
