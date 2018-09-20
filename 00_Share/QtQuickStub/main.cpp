// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QDateTime>
#include "qcvobject.h"

int main(int argc, char *argv[])
{
    qDebug() << QDateTime::currentMSecsSinceEpoch()
             << "QtQuick OpenCV";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QCvObject cvo;
    qmlRegisterType<QCvObject> ("CvObject", 1, 0, "CvObject");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
