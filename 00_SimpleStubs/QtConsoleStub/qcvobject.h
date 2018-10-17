// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#ifndef QCVOBJECT_H
#define QCVOBJECT_H

#include <QObject>

class QCvObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int intVal READ intVal WRITE setIntVal NOTIFY intValChanged)
public:
    explicit QCvObject(QObject *parent = nullptr);
    ~QCvObject();

    Q_INVOKABLE bool setIntValInvokable(int value);

signals:
    void intValChanged(int value);
public slots:
    int intVal();
    void setIntVal(int value);

private:
    int             _intVal;
};

#endif // QCVOBJECT_H
