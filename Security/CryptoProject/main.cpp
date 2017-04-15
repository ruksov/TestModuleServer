#include <QCoreApplication>
#include "cryptoclass.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CryptoClass test;
    qDebug()<<test.GetPublicKey();
    return a.exec();
}
