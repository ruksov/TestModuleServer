#include "session.h"

Session::Session(qintptr t_descriptor, QObject *parent) : QObject(parent)
{
    m_nextBlockBytes = 0;
    m_Socket = new QTcpSocket(this);
    m_Socket->setSocketDescriptor(t_descriptor);

    m_pCtx = SSL_CTX_new(TLS_server_method());   /* create new context from method */
    if ( m_pCtx == NULL )
    {
        qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(m_pCtx, "../cert/server.crt", SSL_FILETYPE_PEM) <= 0 )
    {
       qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(m_pCtx, "../cert/server.key", SSL_FILETYPE_PEM) <= 0 )
    {
       qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(m_pCtx) )
    {
       qDebug()<<"Private key does not match the public certificate\n";
    }
    m_pSSL = SSL_new(m_pCtx);
    SSL_set_fd(m_pSSL, t_descriptor);

}

Session::~Session()
{
    SSL_free(m_pSSL);
}

void Session::SetSocket(qintptr t_descriptor)
{
    m_Socket->setSocketDescriptor(t_descriptor);
    connect(m_Socket, QTcpSocket::disconnected, this, Session::deleteLater);
    connect(m_Socket, QTcpSocket::readyRead, this, Session::slotReadClient);
}

void Session::slotReadClient()
{

    QByteArray msg;
    char buf[2048] = "";
    m_nextBlockBytes = SSL_read(m_pSSL, buf, sizeof(buf));
    if(m_nextBlockBytes > 0)
    {
        msg = QByteArray::fromRawData(buf, sizeof(buf));
        qDebug()<<msg;
        m_nextBlockBytes = 0;
        std::string str("Server recieve message");
        int err = SSL_write(m_pSSL, str.c_str(), str.length());
    }
    else
        qDebug()<<"0 bytes recieved\n";
}

bool Session::DoHandShake()
{
    m_pSSL = SSL_new(m_pCtx);
    SSL_set_fd(m_pSSL, m_Socket->socketDescriptor());
    int err = SSL_accept(m_pSSL);
    int errcode = SSL_get_error(m_pSSL, err);
    while(errcode==SSL_ERROR_WANT_READ || errcode == SSL_ERROR_WANT_WRITE)
    {
        err = SSL_accept(m_pSSL);
        errcode = SSL_get_error(m_pSSL, err);
    }
    connect(m_Socket, QTcpSocket::disconnected, this, Session::deleteLater);
    connect(m_Socket, QTcpSocket::readyRead, this, Session::slotReadClient);
    if(SSL_get_verify_callback(m_pSSL) != X509_V_OK)
    {
//        int errcode = SSL_get_error(m_pSSL, err);
//        qDebug()<<ERR_error_string(ERR_get_error(),NULL)<<errcode;
        qDebug()<<ERR_error_string(ERR_get_error(),NULL);
        emit m_Socket->disconnected();
        return false;
    }
    else
        qDebug()<<"New verify client with cipher "<<SSL_get_cipher (m_pSSL);
    return true;
}
