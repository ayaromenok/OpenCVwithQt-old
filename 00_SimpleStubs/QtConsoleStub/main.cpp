#include <QCoreApplication>
#include "../../00_Share/share/share.h"
#include "qcvobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCvObject qcvo;
    qcvo.setIntVal(10);
    qcvo.setIntValInvokable(7);

    return a.exec();
}
