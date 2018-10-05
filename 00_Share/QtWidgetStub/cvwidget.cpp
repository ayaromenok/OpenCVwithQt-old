// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvwidget.h"
#include <QDebug>
#include <QDateTime>
#include <QGridLayout>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>

#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QCameraViewfinder>

#include "../share/share.h"
#include "../share/cvres.h"

#include <opencv2/opencv.hpp>
#include <QImage>


CvWidget::CvWidget(QWidget *parent)
    : QWidget(parent)
{
    CVQT_TIMESTAMP();

    setWindowTitle("Qt Widget for OpenCV");
    CvRes::imageRgb();
    CvRes::imageRgbFull();
    CvRes::imageRgbPart();
    CvRes::imageRgbStereoLeft();
    CvRes::imageRgbStereoRight();
    _numOfImagePlanes = 0;
    //    _vcLayouts = new QVector<QLayout*>;
    //    _vcLabels  = new QVector<QLabel*>;
    _loutMain = new QGridLayout;
    this->setLayout(_loutMain);
    _appendCameraPlane(Qt::Horizontal);
    _appendImageSmoothPlane(Qt::Horizontal);
    _appendImageEdgeDetectPlane(Qt::Horizontal);
    _appendCameraCalibrationPlane(Qt::Horizontal);

}

CvWidget::~CvWidget()
{
    CVQT_TIMESTAMP();

    if (_cam){
        _cam->unload();
        delete _cam;
    }
}

bool
CvWidget::_appendImageSmoothPlane(Qt::Orientation orient)
{
    CVQT_TIMESTAMP();

    QFrame*      frame = new QFrame();
    QVBoxLayout* loutV = new QVBoxLayout;
    QLabel*      lbOne = new QLabel("Image smooth: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbImg = new QLabel("image");

    CvQtPerf     pc;
    bool result = false;
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

    QPixmap      pixmap("./blurGaussian.jpg");

    lbImg->setPixmap(pixmap);

    loutV->addWidget(lbOne);
    loutV->addWidget(lbImg);

    frame->setLayout(loutV);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(1);

    if (Qt::Vertical == orient )
        _loutMain->addWidget(frame, _numOfImagePlanes, 0);
    else
        _loutMain->addWidget(frame, 0, _numOfImagePlanes);

    _numOfImagePlanes++;
    return result;
}


bool
CvWidget::_appendCameraPlane(Qt::Orientation orient)
{
    CVQT_TIMESTAMP();

    bool result = false;

    QCameraViewfinder*      camViewFinder  = new QCameraViewfinder;
    QPushButton*            btnImgCapture = new QPushButton("capture");
    QVBoxLayout*            loutV = new QVBoxLayout;
    QFrame*                 frame = new QFrame();
    _lbCamCap                = new QLabel("Camera Captured Image");

    loutV->addWidget(btnImgCapture);
    loutV->addWidget(camViewFinder);
    loutV->addWidget(_lbCamCap);
    frame->setLayout(loutV);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(1);

    if (Qt::Vertical == orient )
        _loutMain->addWidget(frame, _numOfImagePlanes, 0);
    else
        _loutMain->addWidget(frame, 0, _numOfImagePlanes);
    _numOfImagePlanes++;

    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        qDebug() << "camera: " << cameraInfo.description();
    }

    _cam = new QCamera(QCameraInfo::defaultCamera());
    _cam->setCaptureMode(QCamera::CaptureStillImage);

    _imgCap = new QCameraImageCapture(_cam);

    _imgCapTimer = new QTimer(this);

#ifdef CAMERA_CAPTURE_VIA_FILE
    //workaround for OSX\iOS\some Windows builds
    _imgCap->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    connect(_imgCap, SIGNAL(imageSaved(int, const QString&)),
        this, SLOT(_imgToFile(int, const QString&)));
#else //CAMERA_CAPTURE_VIA_FILE
    _imgCap->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    connect(_imgCap, &QCameraImageCapture::imageAvailable,
            this, &CvWidget::_imgToBuffer);
#endif //CAMERA_CAPTURE_VIA_FILE

    connect(btnImgCapture, SIGNAL(pressed()),
            this, SLOT (_imgCapture()));
    connect(_imgCapTimer, SIGNAL(timeout()),
            this, SLOT(_imgCapture()));

    camViewFinder->show();
    _cam->setViewfinder(camViewFinder);
    _cam->start();

    //_imgCapTimer->start(500);

    return result;
}


bool
CvWidget::_imgCapture()
{
    CVQT_TIMESTAMP();

    bool result = false;
    _cam->searchAndLock();
#ifdef CAMERA_CAPTURE_VIA_FILE
    _imgCap->capture("./imgCam.jpg");
#else //CAMERA_CAPTURE_VIA_FILE
    _imgCap->capture();
#endif //CAMERA_CAPTURE_VIA_FILE
    _cam->unlock();
    result = true;
    return result;
}

bool
CvWidget::_imgToBuffer(int id, const QVideoFrame &buffer)
{
    CVQT_TIMESTAMP();

    bool result = false;
    QVideoFrame frame(buffer);

    frame.map(QAbstractVideoBuffer::ReadOnly);
//    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
//                frame.pixelFormat());
    int nbytes = frame.mappedBytes();
    QImage imgIn = QImage::fromData(frame.bits(), nbytes).scaledToWidth(360);
    qDebug() << "\t\tinput image format" << imgIn.format()
             << "// 4 - Image::Format_RGB32" << "id" <<id;
    _lbCamCap->setPixmap(QPixmap::fromImage(imgIn));
    return result;
}

bool
CvWidget::_imgToFile(int id, const QString &fName)
{
    CVQT_TIMESTAMP();

    bool result = false;
    QImage imgIn(fName);
    qDebug() << "\t\tinput image format" << imgIn.format()
             << "// 4 - Image::Format_RGB32" << "id" << id;
    _lbCamCap->setPixmap(QPixmap::fromImage(imgIn.scaledToWidth(360)));
    return result;
}

int
CvWidget::_appendCameraCalibrationPlane(Qt::Orientation orient)
{
    CVQT_TIMESTAMP();

    QFrame*      frame = new QFrame();
    QVBoxLayout* loutV = new QVBoxLayout;
    QLabel*      lbOne = new QLabel("Camera calibration: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbImg = new QLabel("image");
    QPixmap    pixmap("./imageRgb.png");

    lbImg->setPixmap(pixmap);

    loutV->addWidget(lbOne);
    loutV->addWidget(lbImg);

    frame->setLayout(loutV);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(1);


    if (Qt::Vertical == orient )
        _loutMain->addWidget(frame, _numOfImagePlanes, 0);
    else
        _loutMain->addWidget(frame, 0, _numOfImagePlanes);


    _numOfImagePlanes++;
    return _numOfImagePlanes;
}

bool
CvWidget::_appendImageEdgeDetectPlane(Qt::Orientation orient)
{
    CVQT_TIMESTAMP();
    bool result = false;
    CvQtPerf pc;

    QFrame*      frame = new QFrame();
    QVBoxLayout* loutV = new QVBoxLayout;
    QLabel*      lbOne = new QLabel("Edge Detection: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbImg = new QLabel("image");


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

    QPixmap    pixmap("./edgeDetectCanny.jpg");
    lbImg->setPixmap(pixmap);

    loutV->addWidget(lbOne);
    loutV->addWidget(lbImg);

    frame->setLayout(loutV);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(1);

    if (Qt::Vertical == orient )
        _loutMain->addWidget(frame, _numOfImagePlanes, 0);
    else
        _loutMain->addWidget(frame, 0, _numOfImagePlanes);

    _numOfImagePlanes++;
    return result;
}


