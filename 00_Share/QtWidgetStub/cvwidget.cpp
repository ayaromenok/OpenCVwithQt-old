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
#include "../share/cvres.h"

CvWidget::CvWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::CvWidget()";
    setWindowTitle("Qt Widget for OpenCV");
    CvRes::getImageRgb();
    _numOfImagePlanes = 0;
//    _vcLayouts = new QVector<QLayout*>;
//    _vcLabels  = new QVector<QLabel*>;
    _loutMain = new QGridLayout;
    this->setLayout(_loutMain);
    appendImagePlane(Qt::Vertical);
    appendImagePlane(Qt::Vertical);
    appendImagePlane(Qt::Vertical);

}

CvWidget::~CvWidget()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::~CvWidget()";
}

int
CvWidget::appendImagePlane(Qt::Orientation orient)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "CvWidget::appendImagePlane()";
    _numOfImagePlanes++;

    QFrame*      frame = new QFrame();
    QVBoxLayout* loutV = new QVBoxLayout;
    QLabel*      lbOne = new QLabel("label one: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbTwo = new QLabel("label two: #"
                                    + QString::number(_numOfImagePlanes));
    QLabel*      lbImg = new QLabel("image");
    QPixmap    pixmap(":/data/len_part.jpg");

    lbImg->setPixmap(pixmap);

    loutV->addWidget(lbOne);
    loutV->addWidget(lbImg);
    loutV->addWidget(lbTwo);
    frame->setLayout(loutV);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(1);

    if (Qt::Vertical == orient )
        _loutMain->addWidget(frame, 0, _numOfImagePlanes);
    else
        _loutMain->addWidget(frame, _numOfImagePlanes, 0);

    return _numOfImagePlanes;
}
