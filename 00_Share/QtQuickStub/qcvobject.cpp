// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "qcvobject.h"
#include <QDebug>
#include <QDateTime>

QCvObject::QCvObject(QObject *parent) : QObject(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "QCvObject::QCvObject()";
    _intVal = 0;
}

QCvObject::~QCvObject()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "QCvObject::~QCvObject()";
}


int
QCvObject::intVal()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "int QCvObject::intVal()";
    return _intVal;
}

void
QCvObject::setIntVal(int value)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "QCvObject::setIntVal(" << value << ");";
    _intVal = value;
}
