#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    m_pSocket = new QTcpSocket(this);
    m_pCtx = SSL_CTX_new(TLS_server_method());

    if(!m_pCtx)
    {
        qDebug()<<ERR_error_string(ERR_get_error(), NULL);
    }

    if(SSL_CTX_use_certificate_file(m_pCtx, "../cert/server.crt", SSL_FILETYPE_PEM)<= 0)
    {
       qDebug()<<ERR_error_string(ERR_get_error(), NULL);
    }

    if ( SSL_CTX_use_PrivateKey_file(m_pCtx, "../cert/server.key", SSL_FILETYPE_PEM) <= 0 )
    {
       qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }

    if ( !SSL_CTX_check_private_key(m_pCtx))
    {
       qDebug()<<"Private key does not match the public certificate\n";
    }
}

Client::~Client()
{
    SSL_free(m_pSSL);
    SSL_CTX_free(m_pCtx);
}

void Client::SetSocket(QTcpSocket &t_socket)
{
    m_pSocket = &t_socket;
}

bool Client::DoHandShake()
{
    int retCode, errorCode;
    m_pSSL = SSL_new(m_pCtx);
    SSL_set_fd(m_pSSL, m_pSocket->socketDescriptor());
    do
    {
        retCode = SSL_accept(m_pSSL);
        errorCode = SSL_get_error(m_pSSL, retCode);
    }while(errorCode == SSL_ERROR_WANT_READ || errorCode == SSL_ERROR_WANT_WRITE);

    if(SSL_get_verify_callback(m_pSSL) != X509_V_OK)
    {
        qDebug()<<"Certificate verify faild!";
        return false;
    }
    else
    {
        qDebug()<<"New verify client with cipher "<<SSL_get_cipher (m_pSSL);
        connect(m_pSocket, QTcpSocket::disconnected, this, Client::deleteLater);
        return true;
    }
}
