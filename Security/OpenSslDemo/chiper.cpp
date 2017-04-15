#include "chiper.h"

Chiper::Chiper(QObject *parent) : QObject(parent)
{
    Initialize();
    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();

    BIO* pemPublic = BIO_new_file("public.pem", "w");
    BIO* pemPrivate = BIO_new_file("private.pem","w");

    BIO* bio = BIO_new(BIO_s_mem());

    if(!BN_set_word(bn, RSA_F4))
    {
        qCritical()<<"Could not create bignum word"<<ERR_error_string(ERR_get_error(),NULL);
    }

    if(!RSA_generate_key_ex(rsa,2048,bn,NULL))
    {
        qCritical()<<"Could not generate RSA pair key"<<ERR_error_string(ERR_get_error(),NULL);
    }

    BN_free(bn);

    m_ptrPrivKey = RSAPrivateKey_dup(rsa);
    m_ptrPubKey = RSAPublicKey_dup(rsa);


//    if(!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL,0, NULL, NULL))
//    {
//        qCritical()<<"Could not write private key to pem"<<ERR_error_string(ERR_get_error(),NULL);
//    }
//    if(!PEM_write_bio_RSAPublicKey(pemPublic, rsa))
//    {
//        qCritical()<<"Could not write public key to pem"<<ERR_error_string(ERR_get_error(),NULL);
//    }

    BIO_free(pemPublic);
    BIO_free(pemPrivate);

    //m_ptrPrivKey = GetPrivateKey("private.pem");
//    m_ptrPrivKey = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
//    if(!m_ptrPrivKey)
//    {
//        qCritical()<<"Could not load private key"<<ERR_error_string(ERR_get_error(),NULL);
//    }


    //m_ptrPubKey = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);
//    m_ptrPubKey = GetPublicKey("public.pem");
//    if(!m_ptrPubKey)
//    {
//        qCritical()<<"Could not load public key"<<ERR_error_string(ERR_get_error(),NULL);
//    }
    RSA_free(rsa);
    BIO* bio2 = BIO_new(BIO_s_mem());
    BUF_MEM* ptrBio = NULL;
    RSA_print(bio2, m_ptrPubKey,0);

    BIO_get_mem_ptr(bio2, &ptrBio);

    m_PublicKey = QString::fromUtf8(ptrBio->data);
    BIO_free(bio2);

}

Chiper::~Chiper()
{
    RSA_free(m_ptrPrivKey);
    RSA_free(m_ptrPubKey);
    Finalize();

}

RSA *Chiper::GetPublicKey(QByteArray &data)
{
    const char* publicKeyStr = data.constData();
    BIO* bio =BIO_new_mem_buf((void*)publicKeyStr, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA* rsaPubKey = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);
    if(!rsaPubKey)
    {
        qCritical()<<"Could not load public key"<<ERR_error_string(ERR_get_error(),NULL);
    }

    BIO_free(bio);
    return rsaPubKey;
}

RSA *Chiper::GetPublicKey(QString filename)
{
    QByteArray data = ReadFile(filename);
    return GetPublicKey(data);
}

RSA *Chiper::GetPrivateKey(QByteArray &data)
{
    const char* privateKeyStr = data.constData();
    BIO* bio =BIO_new_mem_buf((void*)privateKeyStr, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA* rsaPrivKey = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    if(!rsaPrivKey)
    {
        qCritical()<<"Could not load private key"<<ERR_error_string(ERR_get_error(),NULL);
    }

    BIO_free(bio);
    return rsaPrivKey;
}

RSA *Chiper::GetPrivateKey(QString filename)
{
    QByteArray data = ReadFile(filename);
    return GetPrivateKey(data);
}

QByteArray Chiper::EncryptRSA(RSA *key, QByteArray &data)
{
    BIO* bio = BIO_new(BIO_s_mem());
    BIO_write(bio, (void*)m_PublicKey.toStdString().c_str(), m_PublicKey.length());
    RSA* rsa =d2i_RSAPublicKey_bio(bio, NULL);
    QByteArray buffer;
    int dataSize = data.size();
    const unsigned char* str =(const unsigned char*)data.constData();
    int keySize = RSA_size(rsa);

    unsigned char* ed = (unsigned char*)malloc(keySize);

    int resultLen = RSA_public_encrypt(dataSize, str, ed, rsa, RSA_PKCS1_OAEP_PADDING);

    if(resultLen == -1)
    {
        qCritical()<<"Could not encrypt: "<<ERR_error_string(ERR_get_error(),NULL);
        return buffer;
    }

    buffer = QByteArray(reinterpret_cast<char*>(ed), resultLen);

    RSA_free(rsa);
    BIO_free(bio);
    return buffer;
return 0;
}

QByteArray Chiper::DecryptRSA(RSA *key, QByteArray &data)
{
    QByteArray buffer;
    const unsigned char* encryptedData = (const unsigned char*)data.constData();

    int keySize = RSA_size(key);

    unsigned char* ed = (unsigned char*)malloc(keySize);

    int resultLen = RSA_private_decrypt(keySize, encryptedData, ed, key, RSA_PKCS1_OAEP_PADDING);

    if(resultLen == -1)
    {
        qCritical()<<"Could not decrypt: "<<ERR_error_string(ERR_get_error(),NULL);
        return buffer;
    }

    buffer = QByteArray::fromRawData((const char*)ed, resultLen);

    return buffer;
return 0 ;
}

QByteArray Chiper::encryptAES(QByteArray passphrase, QByteArray &data)
{
return 0;
}

QByteArray Chiper::decryptAES(QByteArray passphrase, QByteArray &data)
{
return 0;
}

QByteArray Chiper::randomBytes(int size)
{
return 0;
}

void Chiper::FreeRSAKey(RSA *key)
{

}

void Chiper::Initialize()
{
    ERR_load_CRYPTO_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
}

void Chiper::Finalize()
{
    EVP_cleanup();
    ERR_free_strings();
}

QByteArray Chiper::ReadFile(QString filename)
{
    QByteArray data;
    QFile file(filename);
    if(!file.open(QFile::ReadOnly))
    {
        qCritical()<<file.errorString();
        return data;
    }
    data = file.readAll();
    file.close();
    return data;
}

void Chiper::WriteFile(QString filename, QByteArray &data)
{

}
