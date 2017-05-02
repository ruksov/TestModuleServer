#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <QSsl>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if(!ctx)
    {
        qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }
//    SSL_CTX_set_client_CA_list(ctx, SSL_load_client_CA_file("../../mycert.pem"));

    if(!SSL_CTX_load_verify_locations(ctx, "../ca/ca.crt", NULL))
    {
        qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_set_verify_depth(ctx, 1);
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 1234);
    if(socket.waitForConnected(1000))
        qDebug()<<"TCP connected";
    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, socket.socketDescriptor());


    int err = SSL_connect (ssl);
    int errcode = SSL_get_error(ssl, err);
    while((errcode==SSL_ERROR_WANT_READ || errcode == SSL_ERROR_WANT_WRITE) && socket.state() == QAbstractSocket::ConnectedState)
    {
        err = SSL_connect(ssl);
        errcode = SSL_get_error(ssl, err);
    }
    if(SSL_get_verify_callback(ssl) != X509_V_OK)
    {
        qDebug()<<ERR_error_string(ERR_get_error(),NULL);
    }
    else
    {
        qDebug()<<"Succsesful handeshake"<<SSL_get_cipher (ssl);
        X509* server_cert = SSL_get_peer_certificate(ssl);
        if(server_cert)
        {
            qDebug()<<"Server certificate:";
            qDebug()<<X509_NAME_oneline(X509_get_subject_name(server_cert),0,0);
            qDebug()<<X509_NAME_oneline(X509_get_issuer_name(server_cert),0,0);
            X509_free(server_cert);
        }
    }

    if (err <=0)
      {
             errcode = SSL_get_error(ssl, err);
        switch(errcode)
         {
            case SSL_ERROR_NONE: break;        // Cannot happen if err <=0
            case SSL_ERROR_ZERO_RETURN: fprintf(stderr,"SSL connect returned 0.");
            break;
            case SSL_ERROR_WANT_READ: fprintf(stderr,"SSL connect: Read Error.");
            break;
            case SSL_ERROR_WANT_WRITE: fprintf(stderr,"SSL connect: Write Error.");break;
            case SSL_ERROR_WANT_CONNECT: fprintf(stderr,"SSL connect: Error connect."); break;
            case SSL_ERROR_WANT_ACCEPT: fprintf(stderr,"SSL connect: Error accept."); break;
            case SSL_ERROR_WANT_X509_LOOKUP: fprintf(stderr,"SSL connect error: X509 lookup."); break;
            case SSL_ERROR_SYSCALL: fprintf(stderr,"SSL connect: Error in system call."); break;
            case SSL_ERROR_SSL: fprintf(stderr,"SSL connect: Protocol Error.");
    break;

            default: fprintf(stderr,"Failed SSL connect.");
         }
      }
    else
    {
        QTextStream out(stdout);
        QTextStream in(stdin);
        QString str;

        while (1) {
            char buf[2048];
            in>>str;
            int err = SSL_write(ssl, str.toStdString().c_str(), str.length());
            if(err <= 0)
            {
                errcode = SSL_get_error(ssl, err);
           switch(errcode)
            {
               case SSL_ERROR_NONE: break;        // Cannot happen if err <=0
               case SSL_ERROR_ZERO_RETURN: fprintf(stderr,"SSL connect returned 0.");
               break;
               case SSL_ERROR_WANT_READ: fprintf(stderr,"SSL connect: Read Error.");
               break;
               case SSL_ERROR_WANT_WRITE: fprintf(stderr,"SSL connect: Write Error.");break;
               case SSL_ERROR_WANT_CONNECT: fprintf(stderr,"SSL connect: Error connect."); break;
               case SSL_ERROR_WANT_ACCEPT: fprintf(stderr,"SSL connect: Error accept."); break;
               case SSL_ERROR_WANT_X509_LOOKUP: fprintf(stderr,"SSL connect error: X509 lookup."); break;
               case SSL_ERROR_SYSCALL: fprintf(stderr,"SSL connect: Error in system call."); break;
               case SSL_ERROR_SSL: fprintf(stderr,"SSL connect: Protocol Error.");
       break;

               default: fprintf(stderr,"Failed SSL connect.");
            }
            }
                if(socket.waitForBytesWritten())
                {
                    SSL_read(ssl, buf, 2048);
                    break;
                }
            out<<buf<<'\n';
        }
    }


    return a.exec();
}
