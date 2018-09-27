// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include "cvres.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include "share.h"
CvRes::CvRes(QObject *parent) : QObject(parent)
{
    CVQT_TIMESTAMP();
}

bool
CvRes::imageRgb()
{
    return getImage(ImgType::Rgb);
}

bool
CvRes::imageRgbFull()
{
    return getImage(ImgType::Rgb);
}

bool
CvRes::imageRgbPart()
{
    return getImage(ImgType::RgbPart);
}

bool
CvRes::imageRgbStereoLeft()
{
    return getImage(ImgType::RgbStereoLeft);
}

bool
CvRes::imageRgbStereoRight()
{
    return getImage(ImgType::RgbStereoRight);
}

bool
CvRes::getImage(ImgType type)
{
    CVQT_TIMESTAMP();

    bool result = false;

    switch (type) {
    case ImgType::Rgb:{
        result = getImage(":/data/len_full.png", "./imageRgb.png");
        break;
    }
    case ImgType::RgbPart:{
        result = getImage(":/data/len_part.png", "./imageRgbPart.png");
        break;
    }
    case ImgType::RgbStereoLeft:{
        result = getImage(":/data/640x480x24Left.png", "./imageRgbStereoLeft.png");
        break;
    }
    case ImgType::RgbStereoRight:{
        result = getImage(":/data/640x480x24Right.png", "./imageRgbStereoRight.png");
        break;
    }
    default:{
        qDebug() << "unsupported image type";
        result = false;
        break;
    }
    }

    return result;
}
bool
CvRes::getImage(QString inName, QString outName)
{
    CVQT_TIMESTAMP();

    bool result = false;

    QFile fileIn, fileOut;
    QDir dir;
    fileIn.setFileName(inName);
    fileOut.setFileName(outName);


    if (fileIn.exists()) {
        if (!fileOut.exists()) {
            if (fileIn.copy(outName))
            {
                qDebug() << QDateTime::currentMSecsSinceEpoch()
                         << outName << "is OK";
                result = true;
            } else {
                qDebug() << QDateTime::currentMSecsSinceEpoch()
                         << outName << "is MISSING";
                result = false;
            }
        } else {
            qDebug() << QDateTime::currentMSecsSinceEpoch()
                     << outName << "is OK/already exist";
            result = true;
        }
    } else {
        qDebug() << QDateTime::currentMSecsSinceEpoch()
                 << "predefined  file not found - check Qt resources";
        result = false;
    }
    return result;
}


