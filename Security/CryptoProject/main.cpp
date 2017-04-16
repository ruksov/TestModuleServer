#include <QCoreApplication>
#include "cryptoclass.h"
int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    CryptoClass test;

    QByteArray plain = "The man in black fled into the desert and the ... ";
    QByteArray encrypted = test.EncryptData(test.GetPublicKey(), plain);
    QByteArray decrypted = test.DecryptData(encrypted);
    qDebug()<<plain;
    qDebug()<<encrypted;
    qDebug()<<decrypted;
    return a.exec();
}
