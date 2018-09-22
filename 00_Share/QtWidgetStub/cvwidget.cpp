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

#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QCameraViewfinder>

#include "../share/cvres.h"

CvWidget::CvWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::CvWidget()";
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
    _appendImagePlane(Qt::Horizontal);
    _appendImagePlane(Qt::Horizontal);
    _appendImagePlane(Qt::Horizontal);

}

CvWidget::~CvWidget()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::~CvWidget()";
}

int
CvWidget::_appendImagePlane(Qt::Orientation orient)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::_appendImagePlane()";


    QFrame*      frame = new QFrame();
    QVBoxLayout* loutV = new QVBoxLayout;
    QLabel*      lbOne = new QLabel("label one: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbTwo = new QLabel("label two: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbImg = new QLabel("image");
    QPixmap    pixmap("./imageRgb.png");

    lbImg->setPixmap(pixmap);

    loutV->addWidget(lbOne);
    loutV->addWidget(lbImg);
    loutV->addWidget(lbTwo);
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
CvWidget::_appendCameraPlane(Qt::Orientation orient)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::_setCam(" << orient << ");";
    bool result = false;

    QCameraViewfinder*      camViewFinder  = new QCameraViewfinder;
    QPushButton*            btnImgCapture = new QPushButton("capture");
    QVBoxLayout*            loutV = new QVBoxLayout;
    QFrame*                 frame = new QFrame();

    loutV->addWidget(btnImgCapture);
    loutV->addWidget(camViewFinder);
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
    connect(_imgCap, &QCameraImageCapture::imageAvailable,
            this, &CvWidget::_imgToBuffer);
    connect(btnImgCapture, SIGNAL(pressed()),
            this, SLOT (_imgCapture()));

    camViewFinder->show();
    _cam->setViewfinder(camViewFinder);
    _cam->start();

    return result;
}


bool
CvWidget::_imgCapture()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::_imgCapture();";
    bool result = false;

    return result;
}

bool
CvWidget::_imgToBuffer(int id, const QVideoFrame &buffer)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::_imgToBuffer(" << id <<"," << buffer.size() << ");";
    bool result = false;

    return result;
}
