// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifdef  CVQT_DEBUG_HIGHGUI
#include <QApplication>
#else   // CVQT_DEBUG_HIGHGUI
#include <QGuiApplication>
#endif  // CVQT_DEBUG_HIGHGUI
#include <QQmlApplicationEngine>
#include "../share/cvres.h"
#include "../share/share.h"

#include "qcvobject.h"

int main(int argc, char *argv[])
{
    CVQT_TIMESTAMP();
    qDebug() << QDateTime::currentMSecsSinceEpoch() << " msec since Epoch is\t"
             << QDateTime::currentDateTime();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


#ifdef  CVQT_DEBUG_HIGHGUI
    QApplication app(argc, argv);
#else   // CVQT_DEBUG_HIGHGUI
    QGuiApplication app(argc, argv);
#endif  // CVQT_DEBUG_HIGHGUI
    CvRes::imageRgb();
    CvRes::imageRgbFull();
    CvRes::imageRgbPart();
    CvRes::imageRgbStereoLeft();
    CvRes::imageRgbStereoRight();
    CvRes::imageChecked12x12();

    qmlRegisterType<QCvObject> ("CvObject", 1, 0, "CvObject");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
