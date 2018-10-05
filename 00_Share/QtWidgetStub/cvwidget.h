// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifndef CVWIDGET_H
#define CVWIDGET_H

#include <QWidget>
#include <QImage>
#include <QVideoFrame>

class QGridLayout;
class QLayout;
class QLabel;
class QPushButton;

class QCamera;
class QCameraImageCapture;
class QCameraViewfinder;
class QTimer;

class CvWidget : public QWidget
{
    Q_OBJECT

public:
    CvWidget(QWidget *parent = 0);
    ~CvWidget();

private slots:
    bool _imgCapture();
    bool _imgToBuffer(int id, const QVideoFrame &buffer);
    bool _imgToFile(int id, const QString &fName);   // workaround for OSX/iOS

private:
    bool                     _appendImageSmoothPlane(Qt::Orientation orient);
    int                     _appendCameraCalibrationPlane(Qt::Orientation orient);
    bool                     _appendImageEdgeDetectPlane(Qt::Orientation orient);
    bool                    _appendCameraPlane(Qt::Orientation orient);

    int                     _numOfImagePlanes;
    QGridLayout*            _loutMain;
//    QVector<QLayout*>*      _vcLayouts;
//    QVector<QLabel*>*       _vcLabels;

    QCamera*                _cam;
    QCameraImageCapture*    _imgCap;
    QLabel*                 _lbCamCap;

    QTimer*                 _imgCapTimer;
};

#endif // CVWIDGET_H
