// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifndef CVWIDGET_H
#define CVWIDGET_H

#include <QWidget>
class QGridLayout;
class QLayout;
class QLabel;

class CvWidget : public QWidget
{
    Q_OBJECT

public:
    CvWidget(QWidget *parent = 0);
    ~CvWidget();
private:
    int appendImagePlane(Qt::Orientation orient);

    int                     _numOfImagePlanes;
    QGridLayout*            _loutMain;
//    QVector<QLayout*>*      _vcLayouts;
//    QVector<QLabel*>*       _vcLabels;
};

#endif // CVWIDGET_H
