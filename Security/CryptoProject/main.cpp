#include <QCoreApplication>
#include <gtest/gtest.h>
#include "cryptoclass.h"


struct CryptoTest : ::testing::Test
{
    CryptoClass* pCipher;

    CryptoTest()
    {
        pCipher = new CryptoClass();
    }

    ~CryptoTest()
    {
        delete pCipher;
    }
};


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
