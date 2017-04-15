#include "cryptoclass.h"

CryptoClass::CryptoClass() : m_PrivateKey(RSA_new(), RSA_free), m_PublicKey(RSA_new(), RSA_free)
{
    //Initialize openssl components
    ERR_load_CRYPTO_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL);

    RSA_ptr rsaPair(RSA_new(), RSA_free);
    std::unique_ptr<BIGNUM, decltype(&::BN_free)> pBignum(BN_new(), BN_free);
    BIO_ptr bioPrivate(BIO_new(BIO_s_mem()), BIO_free);
    BIO_ptr bioPublic(BIO_new(BIO_s_mem()), BIO_free);


    if(!BN_set_word(pBignum.get(), RSA_F4))
    {
        qCritical()<<"Could not create bignum word"<<ERR_error_string(ERR_get_error(),NULL);
    }

    //Generate RSA key pair
    if(!RSA_generate_key_ex(rsaPair.get(),2048,pBignum.get(),NULL))
    {
        qCritical()<<"Could not generate RSA key pair"<<ERR_error_string(ERR_get_error(),NULL);
    }

    m_PrivateKey = RSA_ptr(RSAPrivateKey_dup(rsaPair.get()), RSA_free);
    m_PublicKey = RSA_ptr(RSAPublicKey_dup(rsaPair.get()), RSA_free);



//    //Write to bio buffer RSA private key
//    if(!PEM_write_bio_RSAPrivateKey(bioPrivate.get(), rsaPair.get(), NULL, NULL,0, NULL, NULL))
//    {
//        qCritical()<<"Could not write private key to pem"<<ERR_error_string(ERR_get_error(),NULL);
//    }


//    //Write to bio buffer RSA public key
//    if(!PEM_write_bio_RSAPublicKey(bioPublic.get(), rsaPair.get()))
//    {
//        qCritical()<<"Could not write public key to pem"<<ERR_error_string(ERR_get_error(),NULL);
//    }



    BUF_MEM* ptrBio = NULL;
    RSA_print(bioPublic.get(), m_PublicKey.get(),0);

    BIO_get_mem_ptr(bioPublic.get(), &ptrBio);

    m_StrPublicKey = QString::fromUtf8(ptrBio->data);

}

QString CryptoClass::GetPublicKey()
{
    return m_StrPublicKey;
}


