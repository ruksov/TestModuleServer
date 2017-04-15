#ifndef CHIPER_H
#define CHIPER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <memory>

using RSA_ptr = std::shared_ptr<RSA>;


class Chiper : public QObject
{
    Q_OBJECT
public:
    explicit Chiper(QObject *parent = 0);

    ~Chiper();

    /**
     * @brief :oads the public key from a byte array
     * @param data The byte array
     * @return RSA
     */
    RSA* GetPublicKey(QByteArray &data);
    RSA* GetPublicKey(QString filename);

    RSA* GetPrivateKey(QByteArray &data);
    RSA* GetPrivateKey(QString filename);

    QByteArray EncryptRSA(RSA* key, QByteArray &data);
    QByteArray DecryptRSA(RSA* key, QByteArray &data);

    /**
     * @brief Encrypt a byte array with AES 256 CBC
     * @param passphrase
     * @param data The byte array to encrypt
     * @return
     */
    QByteArray encryptAES(QByteArray passphrase, QByteArray &data);


    /**
     * @brief Decrypt a byte array with AES 256 CBC
     * @param passphrase
     * @param data The byte array to decrypt
     * @return
     */
    QByteArray decryptAES(QByteArray passphrase, QByteArray &data);

    /**
     * @brief Get a byte array filled with random information
     * @param size The size of the byte array to generate
     * @return QByteArray
     */
    QByteArray randomBytes(int size);

    /**
     * @brief Frees an RSA key from memory
     * @param key The RSA key
     */
    void FreeRSAKey(RSA* key);

    RSA* m_ptrPubKey;
    RSA* m_ptrPrivKey;
    QString m_PublicKey;

signals:

public slots:

private:


    /**
     * @brief initialize th OpenSSL lib
     */
    void Initialize();

    /**
     * @brief Cleanup after th OpenSSL lib
     */
    void Finalize();

    QByteArray ReadFile(QString filename);

    void WriteFile(QString filename, QByteArray &data);


};

#endif // CHIPER_H
