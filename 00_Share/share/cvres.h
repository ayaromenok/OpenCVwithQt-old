// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifndef CVRES_H
#define CVRES_H

#include <QObject>

class CvRes : public QObject
{
    Q_OBJECT
public:
    explicit CvRes(QObject *parent = nullptr);
    static bool getImageRgb();

signals:

public slots:
private:

};

#endif // CVRES_H
