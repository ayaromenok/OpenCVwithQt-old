// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifndef CVRES_H
#define CVRES_H

#include <QObject>

class CvRes : public QObject
{
    Q_OBJECT
enum class ImgType {RgbFull, RgbPart, RgbStereoLeft, RgbStereoRight, Unknown};
public:
    explicit CvRes(QObject *parent = nullptr);
    static bool imageRgb();
    static bool imageRgbFull();
    static bool imageRgbPart();
    static bool imageRgbStereoLeft();
    static bool imageRgbStereoRight();

signals:

public slots:
private:
    static bool getImage(ImgType type);
    static bool getImage(QString inName, QString outName);
};

#endif // CVRES_H
