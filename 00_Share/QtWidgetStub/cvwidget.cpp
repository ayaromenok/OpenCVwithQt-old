// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvwidget.h"
#include <QDebug>
#include <QDateTime>

CvWidget::CvWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::CvWidget()";
}

CvWidget::~CvWidget()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvWidget::~CvWidget()";
}
