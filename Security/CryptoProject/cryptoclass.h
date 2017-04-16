#pragma once



#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>

#include <memory>
#include <qDebug>

typedef  std::unique_ptr<RSA, decltype(&::RSA_free)> ptrRSA;
typedef  std::unique_ptr<BIO, decltype(&::BIO_free)> ptrBIO;

class CryptoClass
{
public:
    CryptoClass();

    ~CryptoClass();

    /**
     * @brief GetPublicKey
     * @return PEM encoded Public key
     */
    QByteArray GetPublicKey();

    /**
     * @brief Encrypt data used external Public key
     * @param referance on data for encrypt
     * @return encrypted data
     */
    QByteArray EncryptData(QByteArray publicKey, QByteArray &data);

    /**
     * @brief DecryptData
     * @param referance on data for decrypt
     * @return decrypted data
     */
    QByteArray DecryptData(QByteArray &data);

private:

    // RSA key pair

    ptrRSA m_PublicKey;
    ptrRSA m_PrivateKey;

};

