// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifndef SHARE_H
#define SHARE_H
#include <QDebug>
#include <QDateTime>

//! \todo - check, where is __PRETTY_FUNCTION__ is NOT suopprted
/*
#define CVQT_TIMESTAMP() \
    ({ qDebug() << QDateTime::currentMSecsSinceEpoch() << __func__; })
*/

#define CVQT_TIMESTAMP() \
    ({ qDebug() << QDateTime::currentMSecsSinceEpoch() << __PRETTY_FUNCTION__; })

#endif // SHARE_H
