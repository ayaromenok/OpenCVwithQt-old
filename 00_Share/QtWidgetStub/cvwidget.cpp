// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvwidget.h"
#include <QDebug>
#include <QDateTime>
#include "../share/cvres.h"

CvWidget::CvWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::CvWidget()";
    setWindowTitle("Qt Widget for OpenCV");
    CvRes::getImageRgb();
}

CvWidget::~CvWidget()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::~CvWidget()";
}
