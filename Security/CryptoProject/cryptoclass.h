#pragma once



#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>

#include <memory>
#include <qDebug>

typedef  std::unique_ptr<RSA, decltype(&::RSA_free)> RSA_ptr;
typedef  std::unique_ptr<BIO, decltype(&::BIO_free)> BIO_ptr;

class CryptoClass
{
public:
    CryptoClass();

    /**
     * @brief GetPublicKey
     * @return pointer on public RSA key
     */
    QString GetPublicKey();

    /**
     * @brief EncryptData
     * @param referance on data for encrypt
     * @return encrypted data
     */
    QByteArray EncryptData(QString publicKey, QByteArray &data);

    /**
     * @brief DecryptData
     * @param referance on data for decrypt
     * @return decrypted data
     */
    QByteArray DecryptData(QByteArray &data);

private:

    // RSA key pair

    RSA_ptr m_PublicKey;
    RSA_ptr m_PrivateKey;

    QString m_StrPublicKey;
};

