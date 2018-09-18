// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvres.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>

CvRes::CvRes(QObject *parent) : QObject(parent)
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvRes::CvRes()";
}

bool
CvRes::getImageRgb()
{
    qDebug() << QDateTime::currentMSecsSinceEpoch() << "CvRes::getImageRgb()";

    QFile file, fileInFs;
    QString sfName("./imageRgb.jpg");
    QDir dir;
    file.setFileName(":/data/len_full.jpg");
    fileInFs.setFileName(sfName);


    if (file.exists()) {
        if (!fileInFs.exists()) {
            if (file.copy(sfName))
            {
                qDebug() << QDateTime::currentMSecsSinceEpoch()
                         << sfName << "is OK";
            } else {
                qDebug() << QDateTime::currentMSecsSinceEpoch()
                         << sfName << "is MISSING";
                return false;
            }
        } else {
            qDebug() << QDateTime::currentMSecsSinceEpoch()
                     << sfName << "is OK/already exist";
        }
    } else {
        qDebug() << QDateTime::currentMSecsSinceEpoch()
                 << "predefined  file not found - check Qt resources";
    }
    return true;
}
